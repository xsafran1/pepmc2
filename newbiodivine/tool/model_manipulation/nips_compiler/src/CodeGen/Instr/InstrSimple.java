/* NIPS C - New Implementation of Promela Semantics Compiler
 * code generator package - instructions
 * Copyright (C) 2005: Stefan Schuermans <stefan@schuermans.info>
 *                     Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                     Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package CodeGen.Instr;

// a simple instruction
public class InstrSimple extends InstrReal
{
  public final static byte INSTR_SIMPLE_NOP = 1;
  public final static byte INSTR_SIMPLE_ADD = 2;
  public final static byte INSTR_SIMPLE_SUB = 3;
  public final static byte INSTR_SIMPLE_MUL = 4;
  public final static byte INSTR_SIMPLE_DIV = 5;
  public final static byte INSTR_SIMPLE_MOD = 6;
  public final static byte INSTR_SIMPLE_NEG = 7;
  public final static byte INSTR_SIMPLE_NOT = 8;
  public final static byte INSTR_SIMPLE_AND = 9;
  public final static byte INSTR_SIMPLE_OR = 10;
  public final static byte INSTR_SIMPLE_XOR = 11;
  public final static byte INSTR_SIMPLE_SHL = 12;
  public final static byte INSTR_SIMPLE_SHR = 13;
  public final static byte INSTR_SIMPLE_EQ = 14;
  public final static byte INSTR_SIMPLE_NEQ = 15;
  public final static byte INSTR_SIMPLE_LT = 16;
  public final static byte INSTR_SIMPLE_LTE = 17;
  public final static byte INSTR_SIMPLE_GT = 18;
  public final static byte INSTR_SIMPLE_GTE = 19;
  public final static byte INSTR_SIMPLE_BNOT = 20;
  public final static byte INSTR_SIMPLE_BAND = 21;
  public final static byte INSTR_SIMPLE_BOR = 22;
  public final static byte INSTR_SIMPLE_BCHK = 23;
  public final static byte INSTR_SIMPLE_RET = 24;
  public final static byte INSTR_SIMPLE_CHMAX = 25;
  public final static byte INSTR_SIMPLE_CHLEN = 26;
  public final static byte INSTR_SIMPLE_CHFREE = 27;
  public final static byte INSTR_SIMPLE_CHADD = 28;
  public final static byte INSTR_SIMPLE_CHSET = 29;
  public final static byte INSTR_SIMPLE_CHGET = 30;
  public final static byte INSTR_SIMPLE_CHDEL = 31;
  public final static byte INSTR_SIMPLE_CHSORT = 32;
  public final static byte INSTR_SIMPLE_CHROT = 33;
  public final static byte INSTR_SIMPLE_NEX = 34;
  public final static byte INSTR_SIMPLE_NEXZ = 35;
  public final static byte INSTR_SIMPLE_NEXNZ = 36;
  public final static byte INSTR_SIMPLE_FCLR = 37;
  public final static byte INSTR_SIMPLE_PCVAL = 38;
  public final static byte INSTR_SIMPLE_ENAB = 39;
  public final static byte INSTR_SIMPLE_MONITOR = 40;

  private byte kind; // kind of the simple instruction

  // create a new simple instruction
  public InstrSimple( byte kind )
  {
    switch( kind )
    {
      case INSTR_SIMPLE_NOP: this.kind = INSTR_SIMPLE_NOP; break;
      case INSTR_SIMPLE_ADD: this.kind = INSTR_SIMPLE_ADD; break;
      case INSTR_SIMPLE_SUB: this.kind = INSTR_SIMPLE_SUB; break;
      case INSTR_SIMPLE_MUL: this.kind = INSTR_SIMPLE_MUL; break;
      case INSTR_SIMPLE_DIV: this.kind = INSTR_SIMPLE_DIV; break;
      case INSTR_SIMPLE_MOD: this.kind = INSTR_SIMPLE_MOD; break;
      case INSTR_SIMPLE_NEG: this.kind = INSTR_SIMPLE_NEG; break;
      case INSTR_SIMPLE_NOT: this.kind = INSTR_SIMPLE_NOT; break;
      case INSTR_SIMPLE_AND: this.kind = INSTR_SIMPLE_AND; break;
      case INSTR_SIMPLE_OR: this.kind = INSTR_SIMPLE_OR; break;
      case INSTR_SIMPLE_XOR: this.kind = INSTR_SIMPLE_XOR; break;
      case INSTR_SIMPLE_SHL: this.kind = INSTR_SIMPLE_SHL; break;
      case INSTR_SIMPLE_SHR: this.kind = INSTR_SIMPLE_SHR; break;
      case INSTR_SIMPLE_EQ: this.kind = INSTR_SIMPLE_EQ; break;
      case INSTR_SIMPLE_NEQ: this.kind = INSTR_SIMPLE_NEQ; break;
      case INSTR_SIMPLE_LT: this.kind = INSTR_SIMPLE_LT; break;
      case INSTR_SIMPLE_LTE: this.kind = INSTR_SIMPLE_LTE; break;
      case INSTR_SIMPLE_GT: this.kind = INSTR_SIMPLE_GT; break;
      case INSTR_SIMPLE_GTE: this.kind = INSTR_SIMPLE_GTE; break;
      case INSTR_SIMPLE_BNOT: this.kind = INSTR_SIMPLE_BNOT; break;
      case INSTR_SIMPLE_BAND: this.kind = INSTR_SIMPLE_BAND; break;
      case INSTR_SIMPLE_BOR: this.kind = INSTR_SIMPLE_BOR; break;
      case INSTR_SIMPLE_BCHK: this.kind = INSTR_SIMPLE_BCHK; break;
      case INSTR_SIMPLE_RET: this.kind = INSTR_SIMPLE_RET; break;
      case INSTR_SIMPLE_CHMAX: this.kind = INSTR_SIMPLE_CHMAX; break;
      case INSTR_SIMPLE_CHLEN: this.kind = INSTR_SIMPLE_CHLEN; break;
      case INSTR_SIMPLE_CHFREE: this.kind = INSTR_SIMPLE_CHFREE; break;
      case INSTR_SIMPLE_CHADD: this.kind = INSTR_SIMPLE_CHADD; break;
      case INSTR_SIMPLE_CHSET: this.kind = INSTR_SIMPLE_CHSET; break;
      case INSTR_SIMPLE_CHGET: this.kind = INSTR_SIMPLE_CHGET; break;
      case INSTR_SIMPLE_CHDEL: this.kind = INSTR_SIMPLE_CHDEL; break;
      case INSTR_SIMPLE_CHSORT: this.kind = INSTR_SIMPLE_CHSORT; break;
      case INSTR_SIMPLE_CHROT: this.kind = INSTR_SIMPLE_CHROT; break;
      case INSTR_SIMPLE_NEX: this.kind = INSTR_SIMPLE_NEX; break;
      case INSTR_SIMPLE_NEXZ: this.kind = INSTR_SIMPLE_NEXZ; break;
      case INSTR_SIMPLE_NEXNZ: this.kind = INSTR_SIMPLE_NEXNZ; break;
      case INSTR_SIMPLE_FCLR: this.kind = INSTR_SIMPLE_FCLR; break;
      case INSTR_SIMPLE_PCVAL: this.kind = INSTR_SIMPLE_PCVAL; break;
      case INSTR_SIMPLE_ENAB: this.kind = INSTR_SIMPLE_ENAB; break;
      case INSTR_SIMPLE_MONITOR: this.kind = INSTR_SIMPLE_MONITOR; break;
      default: throw new IllegalArgumentException( "InstrSimple called with invalid kind (" + kind + ")" );
    }
  }

  // get kind of simple instruction
  public int getKind( )
  {
    return kind;
  }

  // get text representation
  public String toString( )
  {
    switch( kind )
    {
      case INSTR_SIMPLE_NOP: return "\tNOP\n";
      case INSTR_SIMPLE_ADD: return "\tADD\n";
      case INSTR_SIMPLE_SUB: return "\tSUB\n";
      case INSTR_SIMPLE_MUL: return "\tMUL\n";
      case INSTR_SIMPLE_DIV: return "\tDIV\n";
      case INSTR_SIMPLE_MOD: return "\tMOD\n";
      case INSTR_SIMPLE_NEG: return "\tNEG\n";
      case INSTR_SIMPLE_NOT: return "\tNOT\n";
      case INSTR_SIMPLE_AND: return "\tAND\n";
      case INSTR_SIMPLE_OR: return "\tOR\n";
      case INSTR_SIMPLE_XOR: return "\tXOR\n";
      case INSTR_SIMPLE_SHL: return "\tSHL\n";
      case INSTR_SIMPLE_SHR: return "\tSHR\n";
      case INSTR_SIMPLE_EQ: return "\tEQ\n";
      case INSTR_SIMPLE_NEQ: return "\tNEQ\n";
      case INSTR_SIMPLE_LT: return "\tLT\n";
      case INSTR_SIMPLE_LTE: return "\tLTE\n";
      case INSTR_SIMPLE_GT: return "\tGT\n";
      case INSTR_SIMPLE_GTE: return "\tGTE\n";
      case INSTR_SIMPLE_BNOT: return "\tBNOT\n";
      case INSTR_SIMPLE_BAND: return "\tBAND\n";
      case INSTR_SIMPLE_BOR: return "\tBOR\n";
      case INSTR_SIMPLE_BCHK: return "\tBCHK\n";
      case INSTR_SIMPLE_RET: return "\tRET\n";
      case INSTR_SIMPLE_CHMAX: return "\tCHMAX\n";
      case INSTR_SIMPLE_CHLEN: return "\tCHLEN\n";
      case INSTR_SIMPLE_CHFREE: return "\tCHFREE\n";
      case INSTR_SIMPLE_CHADD: return "\tCHADD\n";
      case INSTR_SIMPLE_CHSET: return "\tCHSET\n";
      case INSTR_SIMPLE_CHGET: return "\tCHGET\n";
      case INSTR_SIMPLE_CHDEL: return "\tCHDEL\n";
      case INSTR_SIMPLE_CHSORT: return "\tCHSORT\n";
      case INSTR_SIMPLE_CHROT: return "\tCHROT\n";
      case INSTR_SIMPLE_NEX: return "\tNEX\n";
      case INSTR_SIMPLE_NEXZ: return "\tNEXZ\n";
      case INSTR_SIMPLE_NEXNZ: return "\tNEXNZ\n";
      case INSTR_SIMPLE_FCLR: return "\tFCLR\n";
      case INSTR_SIMPLE_PCVAL: return "\tPCVAL\n";
      case INSTR_SIMPLE_ENAB: return "\tENAB\n";
      case INSTR_SIMPLE_MONITOR: return "\tMONITOR\n";
      default: return "\t???\n";
    }
  }

  // duplicate this instruction
  public Instr duplicate( )
  {
    return new InstrSimple( kind );
  }
} // public class InstrSimple
