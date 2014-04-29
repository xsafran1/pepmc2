/* NIPS C - New Implementation of Promela Semantics Compiler
 * code generator package - instructions
 * Copyright (C) 2005: Stefan Schuermans <stefan@schuermans.info>
 *                     Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                     Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package CodeGen.Instr;

// a LOOP instruction
public class InstrLoop extends InstrReal
{
  private byte reg; // the register to use
  private String destLabel; // the destination label

  // create a new LOOP instruction
  public InstrLoop( byte reg, String destLabel )
  {
    if( reg >= 8 )
      throw new IllegalArgumentException( "InstrLoop called with invalid register number (" + reg + ")" );
    this.reg = reg;
    this.destLabel = destLabel;
  }

  // get destination label
  public String getDestLabel( )
  {
    return destLabel;
  }

  // get text representation
  public String toString( )
  {
    return "\tLOOP\tr" + ((int)reg & 0xFF) + "\t" + destLabel + "\n";
  }

  // duplicate this instruction
  public Instr duplicate( )
  {
    return new InstrLoop( reg, destLabel );
  }
} // public class InstrLoop
