/* NIPS C - New Implementation of Promela Semantics Compiler
 * code generator package - instructions
 * Copyright (C) 2005: Stefan Schuermans <stefan@schuermans.info>
 *                     Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                     Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package CodeGen.Instr;

// a LVAR instruction
public class InstrLVar extends InstrReal
{
  private boolean sign; // if variable has got a sign
  private int size; // size of variable

  // create a LVAR instruction
  public InstrLVar( boolean sign, int size )
  {
    this.sign = sign;
    if( size != 1 && size != 2 && size != 4 )
      throw new IllegalArgumentException( "InstrLVar called with invalid size (" + size + ")" );
    this.size = size;
  }

  // get parameters
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
    return "\tLVAR\t" + size + (size < 4 ? (sign ? "s\n" : "u\n") : "\n");
  }

  // duplicate this instruction
  public Instr duplicate( )
  {
    return new InstrLVar( sign, size );
  }
} // public class InstrLVar
