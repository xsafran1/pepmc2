/* NIPS C - New Implementation of Promela Semantics Compiler
 * code generator package - instructions
 * Copyright (C) 2005: Stefan Schuermans <stefan@schuermans.info>
 *                     Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                     Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package CodeGen.Instr;

// a print value instruction
public class InstrPrintV extends InstrReal
{
  private String fmt; // format character

  // create a new print value instruction
  public InstrPrintV( String fmt )
  {
    if( fmt.length( ) != 1 )
      throw new IllegalArgumentException( "InstrPrintV called with invalid format character (\"" + fmt + "\")" );
    this.fmt = fmt;
  }

  // get format character
  public String getFmt( )
  {
    return fmt;
  }

  // get text representation
  public String toString( )
  {
    return "\tPRINTV\t" + fmt.getBytes( )[0] + "\n";
  }

  // duplicate this instruction
  public Instr duplicate( )
  {
    return new InstrPrintV( fmt );
  }
} // public class InstrPrintV
