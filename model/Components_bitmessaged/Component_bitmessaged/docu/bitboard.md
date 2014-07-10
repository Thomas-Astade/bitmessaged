bitboard - a successor for Bitmessage protocol
==============================================

Bitmessage protocol
-------------------

[Bitmessage Protocol](https://bitmessage.org) is a new message exchange protocol which addresses the demand for anonymous communication.
Bitmessage is designed as a peer to peer network and needs no server.
There are some very good design ideas in Bitmessage protocol:

- all message content is encrypted (cannot be read by NSA)
- The destination and the source of a message is only known by the recipient (therefor it's impossible to create sociograms)
- It is protected by a POW against Spam
- You don't have to trust the nodes which are transporting the message, because they don't know anything about the message (beside the fact, that it exists)

But there are some drawbacks in Bitmessage protocol:

- Also the messages are protected against Spam with a POW, the network is still prone to Spam, because its nodes are the peers, which normally have a poor Internet connection and very limited memory.
- Because nobody in the network knows the destination (besides the destination itself) its not possible to implement something like a receive notification (e.g. for smart phones)
- Bitmessage will have something called streams, to be scalable for huge user groups. But this part of the protocol is not designed, yet.
- if someone is able to watch the Internet connection of a node, he can identify the message origination and destination, because the node protocol itself is not encrypted.

Bitboard protocol
-----------------

Bitboard protocol is intended to be the successor of Bitmessage protocol. It shall have the same advantages and find solutions for the drawbacks.
This description is not a specification, yet.

Bitboard is **not** a peer to peer network, like Bitmessage. It uses servers. This servers are called the Bitboards.
The Bitboards are web-servers. You may place object on this servers, like you do this in the Bitmessage protocol. Everybody may do this, without authorizing or identifying.
So the objects get nearly anonymous onto the server. For Spam protection there is a POW required, like in Bitmessage protocol.

The objects are encrypted. The fingerprint of the key is **contained** in the object. So it is known, which key is the destination of the message. 
Knowing the destination, the Bitboard can do an out band receive notification. And it is possible to get messages for a certain destination, without downloading much data.
That means, in Bitboard protocol the **destination** of a message is not a secret any more. But the source is still a secret and therefor sociograms are still not possible.

Because Bitboards are servers, the protocol immediately scales very good, the same way email does. A Bitboard address looks like: 43:51:43:a1:b5:fc:8b:b7:0a:3a:a9:b1:0f:66:73:a8@someserver.org
So if I want to send a message to "43:51:43:a1:b5:fc:8b:b7:0a:3a:a9:b1:0f:66:73:a8"@someserver.org" I have to do the following steps:

1. I connect to a bitboard server to get the public key for "43:51:43:a1:b5:fc:8b:b7:0a:3a:a9:b1:0f:66:73:a8". The Key must be located at the Bitboard server "someserver.org" but I can send my request to any bitbord server. It will relay the request to "someserver.org"
2. Create the object, containing the message (encrypted with the public key) a "time to live" and the POW.
3. Upload the object to a bitboard server. (again, the object must be upload to "someserver.org" but any Bitboard will do relay for you)

The recipient will ether get a notification (if "someserver.org" supports it) or will see the object in his in box (like an email).

Some figures in keywords:

* Bitboards use https only!
* There are 3 mandatory object types you may upload to a Bitboard (msg, pubkey, broadcast).
* Bitboard uses gpg encryption for messages and broadcasts. Any key type and length supported by gpg may be used in Bitboard.
* Bitboard messages and broadcasts have mime content. The content is zipped and encrypted. There is a strict size limit for objects on all servers. The proposed value for the size limit is 4096 bytes.
* You can only upload an object to a Bitboard, if there is a corresponding pubkey object on that Bitboard.
* To upload an object you have to calculate a POW for Spam protection.

With at least one (ore multiple) Bitboard servers you can build up message clients for secure communication. You may use the same address (pubkey) on different servers, give automatically some redundency.
Clients can be SMTP gateways, which makes it easy to send and receive Bitboard messages with a standard email client. This is easier, because in Bitboard the recipient of a message is not secret.
In the same way there can be smart phone apps that send and receive Bitboard messages. With a small extension on a Bitboard server, its possible to implement notifications and
on-line status, like you would expect it for a smart phone app.

If we compare Bitboard with Bitmessage we find all drawbacks of bitmessage solved:

* Both protocols hide sociograms. In Bitboard the destination is public, but as long the sender is hidden, sociograms are not possible.
* Bitboard use link level encryption (https) which makes it more difficult to spy a certain client by watching the Internet connection.
* Bitboard can easily be used behind a firewall
* Bitboard is not "no trust". this is a **small drawback**. You have to trust the Bitboard server you are sending your messages from, because this server could make sociograms
* If you use message notification, you have to trust the server where you receive your messages from, because this server can make sociograms, too.
* Both protocols encrypt the content of the message using a strong encryption. It's real end to end encryption, so no one in between can read the message.

Implementation
--------------

The Bitboard server is implemented in PHP. So you can use a cheap managed server from any Internet provider to run a high performant Bitboard server.
The Server must support script (PHP) and a database (SQL). But most Internet providers offer such servers (intentionally for Internet shops) for a reasonably price.


