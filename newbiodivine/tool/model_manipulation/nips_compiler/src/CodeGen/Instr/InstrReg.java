/* NIPS C - New Implementation of Promela Semantics Compiler
 * code generator package - instructions
 * Copyright (C) 2005: Stefan Schuermans <stefan@schuermans.info>
 *                     Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                     Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package CodeGen.Instr;

// a register instruction
public class InstrReg extends InstrReal
{
  public final static byte INSTR_REG_TOP = 1;
  public final static byte INSTR_REG_POP = 2;
  public final static byte INSTR_REG_PUSH = 3;
  public final static byte INSTR_REG_INC = 4;
  public final static byte INSTR_REG_DEC = 5;

  private byte kind; // kind of the register instruction
  private byte reg; // the register to use

  // create a new register instruction
  public InstrReg( byte kind, byte reg )
  {
    switch( kind )
    {
      case INSTR_REG_TOP: this.kind = INSTR_REG_TOP; break;
      case INSTR_REG_POP: this.kind = INSTR_REG_POP; break;
      case INSTR_REG_PUSH: this.kind = INSTR_REG_PUSH; break;
      case INSTR_REG_INC: this.kind = INSTR_REG_INC; break;
      case INSTR_REG_DEC: this.kind = INSTR_REG_DEC; break;
      default: throw new IllegalArgumentException( "InstrReg called with invalid kind (" + kind + ")" );
    }
    if( reg >= 8 )
      throw new IllegalArgumentException( "InstrReg called with invalid register number (" + reg + ")" );
    this.reg = reg;
  }

  // get kind of register instruction
  public byte getKind( )
  {
    return kind;
  }

  // get register number
  public byte getReg( )
  {
    return reg;
  }

  // get text representation
  public String toString( )
  {
    switch( kind )
    {
      case INSTR_REG_TOP: return "\tTOP\tr" + ((int)reg & 0xFF) + "\n";
      case INSTR_REG_POP: return "\tPOP\tr" + ((int)reg & 0xFF) + "\n";
      case INSTR_REG_PUSH: return "\tPUSH\tr" + ((int)reg & 0xFF) + "\n";
      case INSTR_REG_INC: return "\tINC\tr" + ((int)reg & 0xFF) + "\n";
      case INSTR_REG_DEC: return "\tDEC\tr" + ((int)reg & 0xFF) + "\n";
      default: return "\t???\tr" + ((int)reg & 0xFF) + "\n";
    }
  }

  // duplicate this instruction
  public Instr duplicate( )
  {
    return new InstrReg( kind, reg );
  }
} // public class InstrReg
