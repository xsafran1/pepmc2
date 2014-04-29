/* NIPS C - New Implementation of Promela Semantics Compiler
 * code generator package - instructions
 * Copyright (C) 2005: Stefan Schuermans <stefan@schuermans.info>
 *                     Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                     Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package CodeGen.Instr;

// a LDS instruction
public class InstrLoadSpecial extends InstrReal
{
  public final static byte INSTR_LDS_TIMEOUT = 0;
  public final static byte INSTR_LDS_PID = 1;
  public final static byte INSTR_LDS_NRPR = 2;
  public final static byte INSTR_LDS_LAST = 3;
  public final static byte INSTR_LDS_NP = 4;

  private byte special; // which special value to load

  // create a new LDS instruction
  public InstrLoadSpecial( byte special )
  {
    switch( special )
    {
      case INSTR_LDS_TIMEOUT: this.special = INSTR_LDS_TIMEOUT; break;
      case INSTR_LDS_PID: this.special = INSTR_LDS_PID; break;
      case INSTR_LDS_NRPR: this.special = INSTR_LDS_NRPR; break;
      case INSTR_LDS_LAST: this.special = INSTR_LDS_LAST; break;
      case INSTR_LDS_NP: this.special = INSTR_LDS_NP; break;
      default: throw new IllegalArgumentException( "InstrLoadSpecial called with invalid special value (" + special + ")" );
    }
  }

  // get special value
  public byte getSpecial( )
  {
    return special;
  }

  // get text representation
  public String toString( )
  {
    switch( special )
    {
      case INSTR_LDS_TIMEOUT: return "\tLDS\ttimeout\n";
      case INSTR_LDS_PID: return "\tLDS\tpid\n";
      case INSTR_LDS_NRPR: return "\tLDS\tnrpr\n";
      case INSTR_LDS_LAST: return "\tLDS\tlast\n";
      case INSTR_LDS_NP: return "\tLDS\tnp\n";
      default: return "\tLDS\t???\n";
    }
  }

  // duplicate this instruction
  public Instr duplicate( )
  {
    return new InstrLoadSpecial( special );
  }
} // public class InstrLoadSpecial
