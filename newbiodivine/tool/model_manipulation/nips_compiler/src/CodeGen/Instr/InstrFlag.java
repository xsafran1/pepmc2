/* NIPS C - New Implementation of Promela Semantics Compiler
 * code generator package - instructions
 * Copyright (C) 2005: Stefan Schuermans <stefan@schuermans.info>
 *                     Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                     Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package CodeGen.Instr;

// a flag instruction
public class InstrFlag extends InstrReal
{
  public final static byte INSTR_FLAG_FGET = 1;
  public final static byte INSTR_FLAG_FSET = 2;

  private byte kind; // which kind of flag instruction
  private byte flag; // number of flag to get or set

  // create a new flag instruction
  public InstrFlag( byte kind, byte flag )
  {
    switch( kind )
    {
      case INSTR_FLAG_FGET: this.kind = INSTR_FLAG_FGET; break;
      case INSTR_FLAG_FSET: this.kind = INSTR_FLAG_FSET; break;
      default: throw new IllegalArgumentException( "InstrFlag called with invalid kind (" + kind + ")" );
    }
    if( flag > 31 )
      throw new IllegalArgumentException( "InstrFlag called with invalid flag number (" + flag + ")" );
  }

  // get type of instruction
  public int getKind( )
  {
    return kind;
  }

  // get text representation
  public String toString( )
  {
    switch( kind )
    {
      case INSTR_FLAG_FGET: return "\tFGET\t" + ((int)flag & 0xFF) + "\n";
      case INSTR_FLAG_FSET: return "\tFSET\t" + ((int)flag & 0xFF) + "\n";
      default: return "\tF???\t" + ((int)flag & 0xFF) + "\n";
    }
  }

  // duplicate this instruction
  public Instr duplicate( )
  {
    return new InstrFlag( kind, flag );
  }
} // public class InstrFlag
