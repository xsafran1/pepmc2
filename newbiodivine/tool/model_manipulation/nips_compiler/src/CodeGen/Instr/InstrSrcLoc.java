/* NIPS C - New Implementation of Promela Semantics Compiler
 * code generator package - instructions
 * Copyright (C) 2005: Stefan Schuermans <stefan@schuermans.info>
 *                     Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                     Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package CodeGen.Instr;

// a source location "instruction"
public class InstrSrcLoc extends InstrInfo
{
  private String line, column; // the location in the source code

  // create a new source location "instruction"
  // - line and/or column may be null
  public InstrSrcLoc( String line, String column )
  {
    if( line == null )
      this.line = "?";
    else
      this.line = line;
    if( column == null )
      this.column = "?";
    else
      this.column = column;
  }

  // get location
  public String getLine( )
  {
    return line;
  }
  public String getColumn( )
  {
    return column;
  }

  // get text representation
  public String toString( )
  {
    return "!srcloc " + line + " " + column + "\n";
  }

  // duplicate this instruction
  public Instr duplicate( )
  {
    return new InstrSrcLoc( line, column );
  }
} // public class InstrSrcLoc
