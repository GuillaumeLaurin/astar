// ======================================================================
// \title  HiComponent.hpp
// \author glaurin
// \brief  hpp file for HiComponent component implementation class
// ======================================================================

#ifndef Astar_HiComponent_HPP
#define Astar_HiComponent_HPP

#include "Astar/Components/HiComponent/HiComponentComponentAc.hpp"

namespace Astar {

class HiComponent final : public HiComponentComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct HiComponent object
    HiComponent(const char* const compName  //!< The component name
    );

    //! Destroy HiComponent object
    ~HiComponent();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler implementation for command SAY_HI
    //!
    //! Command to issue greeting with maximum length of 20 characters
    void SAY_HI_cmdHandler(FwOpcodeType opCode,              //!< The opcode
                           U32 cmdSeq,                       //!< The command sequence number
                           const Fw::CmdStringArg& greeting  //!< Greeting to repeat in the SayHiEvent event
                           ) override;

    //! Handler implementation for command INTRODUCE_ME
    //!
    //! Command to issue introduce with maximum length of 40 characters
    void INTRODUCE_ME_cmdHandler(
        FwOpcodeType opCode,               //!< The opcode
        U32 cmdSeq,                        //!< The command sequence number
        const Fw::CmdStringArg& introduce  //!< Introduce to repeat in the IntroduceMeEvent event
        ) override;

    U32 m_greetingCount = 0;
};

}  // namespace Astar

#endif
