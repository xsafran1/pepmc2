/* NIPS C - New Implementation of Promela Semantics Compiler
 * code generator package - instructions
 * Copyright (C) 2005: Stefan Schuermans <stefan@schuermans.info>
 *                     Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                     Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package CodeGen.Instr;

// a jump instruction
public class InstrJump extends InstrReal
{
  public final static byte INSTR_JUMP_JMP = 1;
  public final static byte INSTR_JUMP_JMPZ = 2;
  public final static byte INSTR_JUMP_JMPNZ = 3;
  public final static byte INSTR_JUMP_LJMP = 4;
  public final static byte INSTR_JUMP_CALL = 5;
  public final static byte INSTR_JUMP_LCALL = 6;
  public final static byte INSTR_JUMP_NDET = 7;
  public final static byte INSTR_JUMP_ELSE = 8;
  public final static byte INSTR_JUMP_UNLESS = 9;
  public final static byte INSTR_JUMP_LDA = 10;

  private byte kind; // which kind of jump instruction
  private String destLabel; // the destination label

  // create a new jump instruction
  public InstrJump( byte kind, String destLabel )
  {
    switch( kind )
    {
      case INSTR_JUMP_JMP: this.kind = INSTR_JUMP_JMP; break;
      case INSTR_JUMP_JMPZ: this.kind = INSTR_JUMP_JMPZ; break;
      case INSTR_JUMP_JMPNZ: this.kind = INSTR_JUMP_JMPNZ; break;
      case INSTR_JUMP_LJMP: this.kind = INSTR_JUMP_LJMP; break;
      case INSTR_JUMP_CALL: this.kind = INSTR_JUMP_CALL; break;
      case INSTR_JUMP_LCALL: this.kind = INSTR_JUMP_LCALL; break;
      case INSTR_JUMP_NDET: this.kind = INSTR_JUMP_NDET; break;
      case INSTR_JUMP_ELSE: this.kind = INSTR_JUMP_ELSE; break;
      case INSTR_JUMP_UNLESS: this.kind = INSTR_JUMP_UNLESS; break;
      case INSTR_JUMP_LDA: this.kind = INSTR_JUMP_LDA; break;
      default: throw new IllegalArgumentException( "InstrJump called with invalid kind (" + kind + ")" );
    }
    this.destLabel = destLabel;
  }

  // get kind of jump instruction
  public int getKind( )
  {
    return kind;
  }

  // get destination label
  public String getDestLabel( )
  {
    return destLabel;
  }

  // get text representation
  public String toString( )
  {
    switch( kind )
    {
      case INSTR_JUMP_JMP: return "\tJMP\t" + destLabel + "\n";
      case INSTR_JUMP_JMPZ: return "\tJMPZ\t" + destLabel + "\n";
      case INSTR_JUMP_JMPNZ: return "\tJMPNZ\t" + destLabel + "\n";
      case INSTR_JUMP_LJMP: return "\tLJMP\t" + destLabel + "\n";
      case INSTR_JUMP_CALL: return "\tCALL\t" + destLabel + "\n";
      case INSTR_JUMP_LCALL: return "\tLCALL\t" + destLabel + "\n";
      case INSTR_JUMP_NDET: return "\tNDET\t" + destLabel + "\n";
      case INSTR_JUMP_ELSE: return "\tELSE\t" + destLabel + "\n";
      case INSTR_JUMP_UNLESS: return "\tUNLESS\t" + destLabel + "\n";
      case INSTR_JUMP_LDA: return "\tLDA\t" + destLabel + "\n";
      default: return "\t???\t" + destLabel + "\n";
    }
  }

  // duplicate this instruction
  public Instr duplicate( )
  {
    return new InstrJump( kind, destLabel );
  }
} // public class InstrJump
