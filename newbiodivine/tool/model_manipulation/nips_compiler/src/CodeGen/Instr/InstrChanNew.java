/* NIPS C - New Implementation of Promela Semantics Compiler
 * code generator package - instructions
 * Copyright (C) 2005: Stefan Schuermans <stefan@schuermans.info>
 *                     Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                     Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package CodeGen.Instr;

// a CHNEW instruction
public class InstrChanNew extends InstrReal
{
  private byte maxLen, typeLen; // parameters of CHNEW command

  // create a CHNEW instruction
  public InstrChanNew( byte maxLen, byte typeLen )
  {
    this.maxLen = maxLen;
    if( typeLen < 1 )
      throw new IllegalArgumentException( "InstrChanNew called with invalid type length (" + typeLen + ")" );
    this.typeLen = typeLen;
  }

  // get parameters
  public byte getMaxLen( )
  {
    return maxLen;
  }
  public byte getTypeLen( )
  {
    return typeLen;
  }

  // get text representation
  public String toString( )
  {
    return "\tCHNEW\t" + ((int)maxLen & 0xFF) + "\t" + ((int)typeLen & 0xFF) + "\n";
  }

  // duplicate this instruction
  public Instr duplicate( )
  {
    return new InstrChanNew( maxLen, typeLen );
  }
} // public class InstrChanNew
