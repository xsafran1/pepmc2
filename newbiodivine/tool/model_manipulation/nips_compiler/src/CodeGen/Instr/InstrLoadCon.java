/* NIPS C - New Implementation of Promela Semantics Compiler
 * code generator package - instructions
 * Copyright (C) 2005: Stefan Schuermans <stefan@schuermans.info>
 *                     Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                     Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package CodeGen.Instr;

// a LDC instruction
public class InstrLoadCon extends InstrReal
{
  private int constant; // constant parameter of LDC instruction

  // create a LDC instruction
  public InstrLoadCon( int constant )
  {
    this.constant = constant;
  }

  // get constant parameter of LDC instruction
  public int getConstant( )
  {
    return constant;
  }

  // get text representation
  public String toString( )
  {
    return "\tLDC\t" + constant + "\n";
  }

  // duplicate this instruction
  public Instr duplicate( )
  {
    return new InstrLoadCon( constant );
  }
} // public class InstrLoadCon
