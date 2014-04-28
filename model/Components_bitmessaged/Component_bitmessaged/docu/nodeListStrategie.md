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

reliable nodes    {#reliable_node}
==================================

Reliable nodes is what we want to have. So we always try to increase the number of reliable nodes.
That is the reason, why we continuously try to connect to unchecked nodes, too, to find more reliable nodes.
In addition we do a very detailed statistic on all data exchange with nodes, to distinguish reliable nodes from others.

unchecked nodes   {#unchecked_node}
===================================

Unchecked nodes is what we get from others. The others deliver us a time stamp, which we will take as a hint,
which node to test first.
But in general, we cannot trust the information we get from others, because they could be [spoofing nodes](@ref spoofing_nodes)
and give us false information.
For this reason it's important to store the origin of a new node address, so we can identify nodes that 
advertise mainly faulty nodes.

faulty nodes     {#faulty_node}
===============================

Faulty nodes have an implementation error. This can be by intention (than it's a [spoofing node](@ref spoofing_nodes) or by chance, than it is really a faulty node.
In general we do not want to talk to faulty nodes. On the other hand, the programmer might fix
the error and the faulty node may turn into a reliable one, after some time.

So we maintain a list of faulty nodes and don't talk to them for some time (1 hour). After that time we give them a second chance.

spoofing nodes     {#spoofing_node}
===================================

Spoofing nodes have errors by intention to foul the Bitmessage network. We do not talk to that nodes nor do we advertise them.
Unfortunately do they try to hide. The implement a behavior, that is destructive, but is not easy to notice.
So we do our best to detect them, by maintaining a statistic on the nodes behavior. We will have to improve this statistic whenever someone improves the spoofing behavior.

When we identify a spoofing node we put it into the list of spoofing nodes and don't talk to them for some time. because it's such a nasty thing, we will block it for a longer time than faulty nodes (24 hours + another random 1-24 hours).

connected nodes
===============

Connected nodes are the nodes where we are currently connected to. They are important only that far, that we have to take care that we do not connect to the same node twice.



Checks necessary to detect spoofing nodes {#necessary_checks}
=============================================================

Spoofing nodes are not so easy to detect, because in the first glance the behave correct. Only if we add some control statistic to each node connection, we are able to detect them. The following statistic seems suitable:

- store a list of all objects you got offered by a connected node, so you can detect [Duplicate offer nodes](@ref attack_duplicate_offer)
- store a list of all objects offered to a connected node, so you are not in danger to offer them twice.
- store a list of all objects a node requested from you, so you can detect when it asks the same object twice. Because than you are talking to a [Hungry node](@ref attack_hungry_node)
- store the time, when you connected to this node (you will need it for the [Dead node](@ref attack_dead_node) detection)
- make a counter to count the number of objects you download from that node, which are newer than the time you connected to the node. If this number stays zero, for a long period of time, you are talking to a  [Dead node](@ref attack_dead_node) or an [Egoistic node](@ref attack_egoistic_node)
- Try to balance you get requests. Nodes with the dead node counter shows zero should get a better chance to deliver objects, to prove they are reliable.
- Accept only up to 20 _new_ nodes from one node so you got not trapped by a [False node provider](@ref attack_false_node_provider)
- measure the time the node needs for a response (answer time) and the time for transmitting a package of data (transmission time) both values for both directions, giving you 4 statistic values to decide, when you are talking to a [Slow node](@ref attack_slow_node)
- do check the POW (https://bitmessage.org/wiki/Proof_of_work) and the time of each object. So you easily find [Spam nodes](@ref atttack_spam)


Connection strategy
===================

- Try to connect to up to 8 nodes
- Try to connect to 2 [reliable nodes](@ref reliable_node) (if you have that much). Always try "oldest first" so you keep your list up to date.
- If a reliable node refuses to accept the connection block its use for 30 minutes (if you have alternatives. Otherwise you may retry after 1 minute). If it gets older than 2 days, throw it away. We store up to 1000 reliable nodes, but we will certainly never reach that number, because we normally can only connect (and therfore keep updated) to 8x24x2=384 nodes in 2 days.
- Fill the other 6 connections up with [unchecked nodes](@ref unchecked_node) (random choice) to get them checked. If you have a connection to an unchecked node for 30 Minutes without having detected any spoofing or protocol error, move it to the [reliable nodes](@ref reliable_node). It's reliable now. Unchecked nodes which grow older than 2 days are thrown away.
- If an unchecked node refuses to connect, ether throw it away or block its use for 30 minutes. This depends on the number of unchecked nodes we have. If our stock on unchecked nodes is 15000 or bigger it's save to throw away.
- Accept another 32 incoming connections (if our bandwidth allows that much)
- Accept another 8 incoming connections, but only advertise node addresses and close thereafter.
- If we detect a protocol error, we drop the connection and move this node to the [faulty nodes](@ref faulty_node).This will block the whole Ip address (all ports) for one hour. After that time it is removed and may be added to the unreliable nodes again (if someone advertises it)
- If we detect a spoofing, we drop the connection and move this node to the [spoofing nodes](@ref spoofing_node).This will block the whole Ip address (all ports) for 24 hours. After that time it is removed and may be added to the unreliable nodes again (if someone advertises it)
- We advertise only reliable nodes (and ourself because we consider to be reliable).
- Outgoing connections are closed after they exist for 60 minutes to keep things in flow and to increase the database of reliable nodes.





