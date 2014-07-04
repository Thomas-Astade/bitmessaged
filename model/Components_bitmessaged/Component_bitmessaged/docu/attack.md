
Possible attacks for Bitmessage networks {#spoofing_nodes}
==========================================================

I want to talk about certain possible attacks of a Bitmessage network. This is to be aware of this attack types, give them names, so we can talk about them, and for implementing mechanisms, this attacks where detected.

Dead node                {#attack_dead_node}
============================================

A very simple form of attack I'll call "Dead node". A "Dead node" behaves like a correct Bitmessage note at start. It exchanges version information and propagates other nodes (other Dead notes only!). The special (and nasty) thing is, it will not ask for any objects nor propagate any objects.

A Bitmessage client that is trapped by a "Dead node" spent one of its connections for nothing. If it gets into contact with other "Dead nodes" or only with other nodes, which are in contact with other "Dead nodes" themselves, the Bitmessage network is split into islands and will not work any more.

A potential attacker must set up a lot of this nodes, to spoof the network.
But it is possible to setup thousands of this nodes (all with the same IP, but different ports) on one computer! You could also think of using a bot network for this attack.

How to defeat: 
- Be aware, that dead nodes may exist.
- Don't trust nodes, that do not offer objects, at least, if the do not offer objects after you have been connected for some time (you can compare with the number of new objects you get from other nodes).
- Do not connect to nodes, you got offered by a “Dead node”
- Do not propagate the address of a “Dead node” nor addresses you got there.
- Do not limit the number of connections in your node too much.
- maintain a list of spoofing nodes

False node provider      {#attack_false_node_provider}
======================================================

The false node provider attacks your "list of nodes". It sends you thousands of randomly generated node addresses all with a very actual time. If your node list strategy is not aware of that, you will have mainly malfunctioning node addresses in your node list.
It takes time (timeout) to figure out, a node address is not responding. So if things run bad, you cannot get connection any more, because the good addresses get lost under a flood of false addresses.

Especially, because the "False node Provider" may mix some working addresses (to other "False node providers") into the false node list.

How to defeat:
- Limit the number of new node addresses you accept by one single other client
- Don't propagate node addresses you did not test yourself.
- Don't throw away "self tested" node addresses, no matter how perfect the new provided ones look.
- maintain a list of spoofing nodes

Hungry node              {#attack_hungry_node}
==============================================

A "Hungry node" attacks your bandwidth. It will request all objects you offer to it. When it get all of them it will eventually asks them again. As all the other spoofing nodes, it will send you node addresses from other spoofing nodes only.
The "Hungry node" is difficult to defeat, because it's behaviour is identically to a node which connects to the network the first time.
But luckily it is less dangerous than the others, because it can only slow things down, not lock everything.

How to defeat:
- Limit the bandwidth you spend for one single node
- store that node as a potential spoofer in your list of spoofing nodes
- keep enough information on that node in your list of spoofing nodes that you can make the decision if it is spoofing or not during the next times you are connected 

Slow node                {#attack_slow_node}
============================================

The "Slow node" is in effect similar to a "Dead node", it traps your connections. The funny thing is, that a "Slow node" does not make any protocol errors at all, it is simply very VERY slow.

I can immediately create 1000 "Slow nodes" by simply start the PyBitmessage client 1000 times on my computer (different ports).
This 1000 Nodes will send connection request to the outside world an will "catch" 8000 connections, or even more, if I allow incoming connections. But because of my slow Internet connection shared by 1000 clients, the data throughput is nearly zero.

You can attack the network with "Slow nodes" the same way as you can do with "Dead nodes" but you need different methods to detect them. Because "Slow nodes" don't do protocol errors.

How to defeat:
- measure the time, your partner node needs for responses. How long it takes for the version exchange, how long does the node list take and so on. For each detail you measure the time. If it takes longer than a certain threshold, mark this node to be a "Slow node"
- don't propagate "Slow nodes"

Egoistic node             {#attack_egoistic_node}
=================================================

The "Egoistic node" is not intentionally designed to harm the network but it effect it does.
It will start with the possibility to limit the bandwidth of the client, to have enough bandwidth free for other purposes. All in a sudden somebody will notice, that it saves bandwidth, when his client only collects objects but not offer them for download (or only very slow). The "Egoistic node" behaves correct in every other manner. And, at the beginning, it does not harm the network.
But if there are more and more "Egoistic nodes" outside, the network will loose it's performance.

Actually the "Egotistic node" behaves similar to a "Hungry node"

How to defeat:
- measure the upload/download ration of you partners. Give new nodes a "credit" of some objects (1000?). But if a node after a certain time has an upload/download ratio less that a certain limit, you are talking to an egoistic node.
- keep this statistic eventually over multiple connections to that node
- disconnect from "Egoistic nodes"
- don't propagate "Egoistic nodes"

Duplicate offer node       {#attack_duplicate_offer}
====================================================

The "duplicate offer node" attacks my bandwidth by offering the same objects again and again.
is not intentionally designed to harm the network but it effect it does.

How to defeat:
- store the offers you get from one node. If you do not have enough memory to store them all, store only a random subset.
- when a node offers the same object a second time (during the same connection) it's a "Duplicate offer node"
- disconnect from "Duplicate offer nodes"
- don't propagate "Duplicate offer nodes"


confusing node       {#attack_confusing}
========================================

It uses the fact, that object types can not be identified.
There are 4 valid types for objects: "msg", "pubkey", "getpubkey" and "broadcast"
Also they are all totally valid "objects" they are rather different. In the protocol there is no possibilty to detect, what type of object it is. You have to really on what you get told by the other node.
This is used by the "confusing node".

A confusing node propagates objects, but telling a wrong object type. When it gets a pubkey, it propagates the object but telling the others it is e.g. a "msg"

Because the time and the POW is valid, no matter if it's a key or a msg the other nodes will transport this object, but with a false type. Nobody will be able to decode this "msg" because its a key.

Where is the danger?
All nodes which receive the object with the wrong type will never receive it correct. Even if they get the object offered correct, they will not download it, because they possess it already and the type is not part of the offer.

How to defeat:
Only a protocol change can solve this problem!


Spam node       {#attack_spam}
==============================

The most obvious one at the end. Spam nodes try to flood the network with tons of objects. As each object in bitmessage contains the POW (https://bitmessage.org/wiki/Proof_of_work) this is taken to reduce Spam. A node can only Spam by sending objects with false POW or old objects. Its to CPU consumptive to effectively Spam with correct generated objects.

How to defeat:
- Check the time of every received object. If it is older than 2 days + (some small time which comes from time difference) it's a "Spam node".
- Check the POW of each object. If the POW is wrong do not advertise this object, but through it away. Nodes that offer objects with wrong POW are "Spam nodes"
- disconnect from "Spam nodes"
- don't propagate "Spam nodes"



