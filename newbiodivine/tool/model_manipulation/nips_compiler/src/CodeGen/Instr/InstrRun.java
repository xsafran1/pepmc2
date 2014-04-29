/* NIPS C - New Implementation of Promela Semantics Compiler
 * code generator package - instructions
 * Copyright (C) 2005: Stefan Schuermans <stefan@schuermans.info>
 *                     Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                     Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package CodeGen.Instr;

// a RUN instruction
public class InstrRun extends InstrReal
{
  private byte localSz, paramCnt; // parameters of RUN command
  private String destLabel; // the destination label
  private boolean isLong; // if to use long version of RUN instruction

  // create a RUN instruction
  public InstrRun( byte localSz, byte paramCnt, String destLabel, boolean isLong )
  {
    this.localSz = localSz;
    this.paramCnt = paramCnt;
    this.destLabel = destLabel;
    this.isLong = isLong;
  }

  // get parameters
  public byte getLocalSz( )
  {
    return localSz;
  }
  public byte getParamCnt( )
  {
    return paramCnt;
  }
  public String getDestLabel( )
  {
    return destLabel;
  }
  public boolean isLong( )
  {
    return isLong;
  }

  // get text representation
  public String toString( )
  {
    return "\t" + (isLong ? "L" : "") +  "RUN\t" + ((int)localSz & 0xFF) + "\t" + ((int)paramCnt & 0xFF) + "\t" + destLabel + "\n";
  }

  // duplicate this instruction
  public Instr duplicate( )
  {
    return new InstrRun( localSz, paramCnt, destLabel, isLong );
  }
} // public class InstrRun
