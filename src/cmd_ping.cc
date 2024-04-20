#include "cmd_ping.h"
#include "client.h"

namespace pikiwidb {

PingCmd::PingCmd(const std::string& name, int16_t arity)
    : BaseCmd(name, arity, kCmdFlagsWrite, kAclCategoryWrite | kAclCategoryList) {}

bool PingCmd::DoInitial(PClient* client) { return true; }

void PingCmd::DoCmd(PClient* client) { client->SetRes(CmdRes::kPong, "PONG"); }
}  // namespace pikiwidb