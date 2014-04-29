/* NIPS C - New Implementation of Promela Semantics Compiler
 * code generator package - instructions
 * Copyright (C) 2005: Stefan Schuermans <stefan@schuermans.info>
 *                     Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                     Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package CodeGen.Instr;

// a STEP instruction
public class InstrStep extends InstrReal
{
  public final static byte INSTR_STEP_NORM = 0;
  public final static byte INSTR_STEP_ATOM = 1;
  public final static byte INSTR_STEP_INVIS = 2;
  public final static byte INSTR_STEP_TERM = 3;

  private byte mode; // mode to complete the step in

  // create a new STEP instruction
  public InstrStep( byte mode )
  {
    switch( mode )
    {
      case INSTR_STEP_NORM: this.mode = INSTR_STEP_NORM; break;
      case INSTR_STEP_ATOM: this.mode = INSTR_STEP_ATOM; break;
      case INSTR_STEP_INVIS: this.mode = INSTR_STEP_INVIS; break;
      case INSTR_STEP_TERM: this.mode = INSTR_STEP_TERM; break;
      default: throw new IllegalArgumentException( "InstrReg called with invalid mode (" + mode + ")" );
    }
  }

  // get mode
  public byte getMode( )
  {
    return mode;
  }

  // get text representation
  public String toString( )
  {
    switch( mode )
    {
      case INSTR_STEP_NORM: return "\tSTEP\tN\t0\n";
      case INSTR_STEP_ATOM: return "\tSTEP\tA\t0\n";
      case INSTR_STEP_INVIS: return "\tSTEP\tI\t0\n";
      case INSTR_STEP_TERM: return "\tSTEP\tT\t0\n";
      default: return "\tSTEP\t?\t0\n";
    }
  }

  // duplicate this instruction
  public Instr duplicate( )
  {
    return new InstrStep( mode );
  }
} // public class InstrStep
