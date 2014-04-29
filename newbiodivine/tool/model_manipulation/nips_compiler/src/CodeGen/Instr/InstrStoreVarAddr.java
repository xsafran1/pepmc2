/* NIPS C - New Implementation of Promela Semantics Compiler
 * code generator package - instructions
 * Copyright (C) 2005: Stefan Schuermans <stefan@schuermans.info>
 *                     Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                     Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package CodeGen.Instr;

// a STVA instruction
public class InstrStoreVarAddr extends InstrReal
{
  private boolean global; // if variable is global
  private boolean sign; // if variable has got a sign
  private int size; // size of variable
  private byte addr; // address of variable

  // create a STVA instruction
  public InstrStoreVarAddr( boolean global, boolean sign, int size, byte addr )
  {
    this.global = global;
    this.sign = sign;
    if( size != 1 && size != 2 && size != 4 )
      throw new IllegalArgumentException( "InstrStoreVarAddr called with invalid size (" + size + ")" );
    this.size = size;
    this.addr = addr;
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
  public byte getAddr( )
  {
    return addr;
  }

  // get text representation
  public String toString( )
  {
    return "\tSTVA\t" + (global ? "G\t" : "L\t") + size
                      + (size < 4 ? (sign ? "s\t" : "u\t") : "\t")
                      + ((int)addr & 0xFF) + "\n";
  }

  // duplicate this instruction
  public Instr duplicate( )
  {
    return new InstrStoreVarAddr( global, sign, size, addr );
  }
} // public class InstrStoreVarAddr
