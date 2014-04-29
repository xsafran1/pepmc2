/* NIPS C - New Implementation of Promela Semantics Compiler
 * code generator package - instructions
 * Copyright (C) 2005: Stefan Schuermans <stefan@schuermans.info>
 *                     Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                     Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package CodeGen.Instr;

// a flags "instruction"
public class InstrFlags extends InstrReal
{
  public final static int INSTR_FLAGS_PROGRESS = 0x00000001;
  public final static int INSTR_FLAGS_ACCEPT = 0x00000002;

  private int flags; // flags to set

  // create a new flags "instruction"
  public InstrFlags( int flags )
  {
    if( (flags & ~INSTR_FLAGS_PROGRESS & ~INSTR_FLAGS_ACCEPT) != 0 )
      throw new IllegalArgumentException( "InstrFlags called with invalid flags (" + flags + ")" );
    this.flags = flags;
  }

  // get flags
  public int getFlags( )
  {
    return flags;
  }

  // get text representation
  public String toString( )
  {
    if( flags == 0 )
      return "";
    String str = "!flags";
    if( (flags & INSTR_FLAGS_PROGRESS) != 0 )
      str = str + " progress";
    if( (flags & INSTR_FLAGS_ACCEPT) != 0 )
      str = str + " accept";
    return str + "\n";
  }

  // duplicate this instruction
  public Instr duplicate( )
  {
    return new InstrFlags( flags );
  }
} // public class InstrFlags
