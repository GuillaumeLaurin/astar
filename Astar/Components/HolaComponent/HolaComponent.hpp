// ======================================================================
// \title  HolaComponent.hpp
// \author glaurin
// \brief  hpp file for HolaComponent component implementation class
// ======================================================================

#ifndef Astar_HolaComponent_HPP
#define Astar_HolaComponent_HPP

#include "Astar/Components/HolaComponent/HolaComponentComponentAc.hpp"

namespace Astar {

class HolaComponent final : public HolaComponentComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct HolaComponent object
    HolaComponent(const char* const compName  //!< The component name
    );

    //! Destroy HolaComponent object
    ~HolaComponent();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler implementation for command SAY_HOLA
    //!
    //! TODO
    void SAY_HOLA_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                             U32 cmdSeq,           //!< The command sequence number
                             const Fw::CmdStringArg& introduce) override;
};

}  // namespace Astar

#endif
