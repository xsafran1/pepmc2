/* NIPS C - New Implementation of Promela Semantics Compiler
 * code generator package - instructions
 * Copyright (C) 2005: Stefan Schuermans <stefan@schuermans.info>
 *                     Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                     Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package CodeGen.Instr;

// a LDV instruction
public class InstrLoadVar extends InstrReal
{
  private boolean global; // if variable is global
  private boolean sign; // if variable has got a sign
  private int size; // size of variable

  // create a LDV instruction
  public InstrLoadVar( boolean global, boolean sign, int size )
  {
    this.global = global;
    this.sign = sign;
    if( size != 1 && size != 2 && size != 4 )
      throw new IllegalArgumentException( "InstrLoadVar called with invalid size (" + size + ")" );
    this.size = size;
  }

  // get parameters
  public boolean getGlobal( )
  {
    return global;
  }
  public boolean getSign( )
  {
    return sign;
  }
  public int getSize( )
  {
    return size;
  }

  // get text representation
  public String toString( )
  {
    return "\tLDV\t" + (global ? "G\t" : "L\t") + size
                     + (size < 4 ? (sign ? "s\n" : "u\n") : "\n");
  }

  // duplicate this instruction
  public Instr duplicate( )
  {
    return new InstrLoadVar( global, sign, size );
  }
} // public class InstrLoadVar
