//~~ std::string getTypeStr() [object] ~~
switch (myType) {
    case message::version: return "version";
    case message::verack: return "verack";
    case message::addr: return "addr";
    case message::inv: return "inv";
    case message::getdata: return "getdata";
    case message::getpubkey: return "getpubkey";
    case message::pubkey: return "pubkey";
    case message::msg: return "msg";
    case message::broadcast: return "broadcast";
    case message::object: return "object";
    case message::unknown: return "unknown";
};

return "unknown";