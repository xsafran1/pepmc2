/* NIPS C - New Implementation of Promela Semantics Compiler
 * code generator package - instructions
 * Copyright (C) 2005: Stefan Schuermans <stefan@schuermans.info>
 *                     Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                     Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package CodeGen.Instr;

// a fixed offset channel instruction
public class InstrChanOfs extends InstrReal
{
  public final static byte INSTR_CHANOFS_CHSETO = 1;
  public final static byte INSTR_CHANOFS_CHGETO = 2;

  private byte kind; // kind of the fixed offset channel instruction
  private byte ofs; // the offset to access

  // create a new fixed offset channel instruction
  public InstrChanOfs( byte kind, byte ofs )
  {
    switch( kind )
    {
      case INSTR_CHANOFS_CHSETO: this.kind = INSTR_CHANOFS_CHSETO; break;
      case INSTR_CHANOFS_CHGETO: this.kind = INSTR_CHANOFS_CHGETO; break;
      default: throw new IllegalArgumentException( "InstrChanOfs called with invalid kind (" + kind + ")" );
    }
    this.ofs = ofs;
  }

  // get kind of fixed offset channel instruction
  public byte getKind( )
  {
    return kind;
  }

  // get offset
  public byte getOfs( )
  {
    return ofs;
  }

  // get text representation
  public String toString( )
  {
    switch( kind )
    {
      case INSTR_CHANOFS_CHSETO: return "\tCHSETO\t" + ((int)ofs & 0xFF) + "\n";
      case INSTR_CHANOFS_CHGETO: return "\tCHGETO\t" + ((int)ofs & 0xFF) + "\n";
      default: return "\t???\t" + ((int)ofs & 0xFF) + "\n";
    }
  }

  // duplicate this instruction
  public Instr duplicate( )
  {
    return new InstrChanOfs( kind, ofs );
  }
} // public class InstrChanOfs
