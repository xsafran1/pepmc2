/* NIPS C - New Implementation of Promela Semantics Compiler
 * code generator package - instructions
 * Copyright (C) 2005: Stefan Schuermans <stefan@schuermans.info>
 *                     Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                     Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package CodeGen.Instr;

// a label "instruction" - only a label, not really an instruction
public class InstrLabel extends InstrReal
{
  private String label; // the label

  // create a new label "instruction"
  public InstrLabel( String label )
  {
    this.label = label;
  }

  // get label
  public String getLabel( )
  {
    return label;
  }

  // get text representation
  public String toString( )
  {
    return label + ":\n";
  }

  // duplicate this instruction
  public Instr duplicate( )
  {
    return new InstrLabel( label );
  }
} // public class InstrLabel
