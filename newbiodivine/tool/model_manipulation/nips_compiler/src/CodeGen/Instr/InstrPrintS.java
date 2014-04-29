/* NIPS C - New Implementation of Promela Semantics Compiler
 * code generator package - instructions
 * Copyright (C) 2005: Stefan Schuermans <stefan@schuermans.info>
 *                     Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                     Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package CodeGen.Instr;

// a print string instruction
public class InstrPrintS extends InstrReal
{
  private short strNo; // number of string to print

  // create a new print instruction
  public InstrPrintS( short strNo )
  {
    this.strNo = strNo;
  }

  // get number of string to print
  public short getStrNo( )
  {
    return strNo;
  }

  // get text representation
  public String toString( )
  {
    return "\tPRINTS\t" + strNo + "\n";
  }

  // duplicate this instruction
  public Instr duplicate( )
  {
    return new InstrPrintS( strNo );
  }
} // public class InstrPrintS
