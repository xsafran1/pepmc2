/* NIPS C - New Implementation of Promela Semantics Compiler
 * code generator package - instructions
 * Copyright (C) 2005: Stefan Schuermans <stefan@schuermans.info>
 *                     Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                     Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package CodeGen.Instr;

// a ICHK instruction
public class InstrIdxCheck extends InstrReal
{
  private byte arraySize; // size of array to check index for

  // create a new ICHK instruction
  public InstrIdxCheck( byte arraySize )
  {
    this.arraySize = arraySize;
  }

  // get text representation
  public String toString( )
  {
    return "\tICHK\t" + ((int)arraySize & 0xFF) + "\n";
  }

  // duplicate this instruction
  public Instr duplicate( )
  {
    return new InstrIdxCheck( arraySize );
  }
} // public class InstrIdxCheck
