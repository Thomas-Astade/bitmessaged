Possible attacks for bitmessage networks
========================================

I want to talk about certain possible attacks of a Bitmessage network. This is to be aware of this attack types, give them names, so we can talk about them, and for implementing mechanisms, this attacks where detected.

Dead node                {#attack_dead_node}
---------

A very simple form of attack I'll call "Dead node". A "Dead node" behaves like a correct Bitmessage note at start. It exchanges Version information and propagates other nodes (other Dead notes only!). The special (and nasty) thing is, it will not ask for any objects nor propagate any objects.

A Bitmessage client that is trapped by a "Dead node" spent one of its connections for nothing. If it gets into contact with other "Dead nodes" or only with other nodes, which are in contact with other "Dead nodes" themselves, the Bitmessage network is split into islands and will not work any more.

A potential attacker must set up a lot of this nodes, to spoof the network.
But it is possible to setup thousands of this nodes (all with the same IP, but different ports) on one computer! You could also think of using a bot network for this attack.

How to defeat: 
- Be aware, that dead nodes may exist.
- Don't trust nodes, that do not offer objects, at least, if the do not offer objects after you have been connected for some time (you can compare with the number of objects you get from other nodes).
- Do not connect to nodes, you got offered by a “Dead node”
- Do not propagate the address of a “Dead node” nor addresses you got there.


