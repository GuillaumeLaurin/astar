// ======================================================================
// \title  HolaComponent.cpp
// \author glaurin
// \brief  cpp file for HolaComponent component implementation class
// ======================================================================

#include "Astar/Components/HolaComponent/HolaComponent.hpp"

namespace Astar {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

HolaComponent ::HolaComponent(const char* const compName) : HolaComponentComponentBase(compName) {}

HolaComponent ::~HolaComponent() {}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void HolaComponent ::SAY_HOLA_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, const Fw::CmdStringArg& introduce) {
    Fw::LogStringArg eventHola(introduce.toChar());

    this->log_ACTIVITY_HI_SayHolaEvent(eventHola);

    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

}  // namespace Astar
