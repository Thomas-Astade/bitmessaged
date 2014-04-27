strategy to maintain the node list
==================================

during its connections the client gets in knowledge of a big number of other nodes.
It has to organize them in some way and offer this knowledge to other nodes.

The nodes may have different quality. There may be nodes who are:
- reliable nodes (nodes which have proven to work correct and have a good performance)
- unchecked nodes (nodes we got from somewhere, not yet tested ourself)
- faulty nodes (nodes which do obviously wrong things)
- [spoofing nodes](@ref spoofing_nodes) (nodes which are designed do spoof the network)
- connected nodes (nodes where we currently are connected to)

reliable nodes
==============

Reliable nodes is what we want to have. So we always try to increase the number of reliable nodes.
That is the reason, why we continuously try to connect to unchecked nodes, too, to find more reliable nodes.
In addition we do a very detailed statistic on all data exchange with nodes, to distinguish reliable nodes from others.

unchecked nodes
===============

Unchecked nodes is what we get from others. The others deliver us a time stamp, which we will take as a hint,
which node to test first.
But in general, we cannot trust the information we get from others, because they could be [spoofing nodes](@ref spoofing_nodes)
and give us false information.
For this reason it's important to store the origin of a new node address, so we can identify nodes that 
advertise mainly faulty nodes.

faulty nodes
============

Faulty nodes have an implementation error. This can be by intention (than it's a [spoofing node](@ref spoofing_nodes) or by chance, than it is really a faulty node.
In general we do not want to talk to faulty nodes. On the other hand, the programmer might fix
the error and the faulty node may turn into a reliable one, after some time.

So we maintain a list of faulty nodes and don't talk to them for some time (1 hour). After that time we give them a second chance.

[spoofing nodes](@ref spoofing_nodes)
=====================================

Spoofing nodes have errors by intention to foul the Bitmessage network. We do not talk to that nodes nor do we advertise them.
Unfortunately do they try to hide. The implement a behavior, that is destructive, but is not easy to notice.
So we do our best to detect them, by maintaining a statistic on the nodes behavior. We will have to improve this statistic whenever someone improves the spoofing behavior.

When we identify a spoofing node we put it into the list of spoofing nodes and don't talk to them for some time. because it's such a nasty thing, we will block it for a longer time than faulty nodes (24 hours + another random 1-24 hours).

connected nodes
===============

Connected nodes are the nodes where we are currently connected to. They are important only that far, that we have to take care that we do not connect to the same node twice.









