/* NIPS C - New Implementation of Promela Semantics Compiler
 * code generator package - instructions
 * Copyright (C) 2005: Stefan Schuermans <stefan@schuermans.info>
 *                     Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                     Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package CodeGen.Instr;

// a GLOBSZ/LOCSZ instruction
public class InstrSize extends InstrReal
{
  public final static byte INSTR_SIZE_GLOBSZ = 1;
  public final static byte INSTR_SIZE_LOCSZ = 2;

  private byte kind; // kind of the GLOBSZ/LOCSZ instruction
  private byte sz; // new size of global/local variables

  // create a GLOBSZ/LOCSZ instruction
  public InstrSize( byte kind, byte sz )
  {
    switch( kind )
    {
      case INSTR_SIZE_GLOBSZ: this.kind = INSTR_SIZE_GLOBSZ; break;
      case INSTR_SIZE_LOCSZ: this.kind = INSTR_SIZE_LOCSZ; break;
      default: throw new IllegalArgumentException( "InstrSize called with invalid kind (" + kind + ")" );
    }
    this.sz = sz;
  }

  // get kind of GLOBSZ/LOCSZ instruction
  public byte getKind( )
  {
    return kind;
  }

  // get size of global/local variables
  public byte getSz( )
  {
    return sz;
  }

  // get text representation
  public String toString( )
  {
    switch( kind )
    {
      case INSTR_SIZE_GLOBSZ: return "\tGLOBSZ\t" + ((int)sz & 0xFF) + "\n";
      case INSTR_SIZE_LOCSZ: return "\tLOCSZ\t" + ((int)sz & 0xFF) + "\n";
      default: return "\t???SZ\t" + ((int)sz & 0xFF) + "\n";
    }
  }

  // duplicate this instruction
  public Instr duplicate( )
  {
    return new InstrSize( kind, sz );
  }
} // public class InstrSize
