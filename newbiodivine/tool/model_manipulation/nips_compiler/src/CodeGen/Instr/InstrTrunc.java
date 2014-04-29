/* NIPS C - New Implementation of Promela Semantics Compiler
 * code generator package - instructions
 * Copyright (C) 2005: Stefan Schuermans <stefan@schuermans.info>
 *                     Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                     Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package CodeGen.Instr;

// a TRUNC instruction
public class InstrTrunc extends InstrReal
{
  private byte bits; // bits parameter of LDC instruction

  // create a TRUNC instruction
  public InstrTrunc( byte bits )
  {
    if( bits < -31 || bits == 0 || bits > 32 )
      throw new IllegalArgumentException( "InstrTrunc called with invalid bit count (" + bits + ")" );
    this.bits = bits;
  }

  // get number of bits
  public byte getBits( )
  {
    return bits;
  }

  // get text representation
  public String toString( )
  {
    return "\tTRUNC\t" + bits + "\n";
  }

  // duplicate this instruction
  public Instr duplicate( )
  {
    return new InstrTrunc( bits );
  }
} // public class InstrLoadTrunc
