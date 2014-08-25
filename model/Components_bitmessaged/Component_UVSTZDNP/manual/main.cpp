// @file

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "knowledge.h"
#include <iostream>
#include <fstream>

static pthread_t thread[4];
static volatile bool keepRunning = true;
static volatile int isRunning = 0;
data::knowledge* database;

void save()
{
    printf("saving objects ...\n");
    std::ofstream myfile;
    myfile.open (".bitmessaged.obj", std::ofstream::binary | std::ofstream::trunc);

    std::set<protocol::inventory_vector> v2Objects = database->getObjects(2);
    
    for (std::set<protocol::inventory_vector>::iterator it = v2Objects.begin(); it != v2Objects.end(); it++)
    {
        protocol::object o = database->getObject(*it);
        myfile << o;
    }
    
    std::set<protocol::inventory_vector> v3Objects = database->getObjects(3);
    
    for (std::set<protocol::inventory_vector>::iterator it = v3Objects.begin(); it != v3Objects.end(); it++)
    {
        protocol::object o = database->getObject(*it);
        myfile << o;
    }

    myfile.close();
}

void load()
{
    printf("loading objects ...\n");
    std::ifstream myfile;
    myfile.open (".bitmessaged.obj", std::ofstream::binary);
    if (myfile.is_open())
    {
        while (!myfile.eof())
        {
            protocol::object o;
            myfile >> o;
            if (!o.isValid())
                break;
            database->addObject(0,o);
        }
    }
    myfile.close();
}

void *aThread( void *ptr )
{
    isRunning++;
    load();
    while (keepRunning)
    {
        for (int i = 0; i < 360; i++)
            if (keepRunning)
                sleep(10);
        save();
    }
    isRunning--;
    return 0;
}

extern "C" {
void init_plugin(data::knowledge& data)
{
    database = &data;
    pthread_create( &thread[0], NULL, aThread, 0);
    printf("save plugin initialized\n");
}

void shutdown_plugin()
{
    keepRunning = false;
    while (isRunning)
        ;
    printf("save plugin shut down\n");
}
}