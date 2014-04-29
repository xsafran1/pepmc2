/* NIPS C - New Implementation of Promela Semantics Compiler
 * code generator package - instructions
 * Copyright (C) 2005: Stefan Schuermans <stefan@schuermans.info>
 *                     Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                     Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package CodeGen.Instr;

// a structure information "instruction"
public class InstrStrInf extends InstrInfo
{
  public static final byte INSTR_STR_INF_BEGIN = 1;
  public static final byte INSTR_STR_INF_END = 2;
  public static final byte INSTR_STR_INF_MIDDLE = 3;

  private byte code; // begin/end/... of some structure
  private String type; // what kind of structure begins or ends here (e.g. proc, block)
  private String name; // optional name of the structure (e.g. proctype name)

  // create a new source location "instruction"
  // - name may be null
  public InstrStrInf( byte code, String type, String name )
  {
    switch( code )
    {
      case INSTR_STR_INF_BEGIN: this.code = INSTR_STR_INF_BEGIN; break;
      case INSTR_STR_INF_END: this.code = INSTR_STR_INF_END; break;
      case INSTR_STR_INF_MIDDLE: this.code = INSTR_STR_INF_MIDDLE; break;
      default: throw new IllegalArgumentException( "InstrStrInf called with invalid code (" + code + ")" );
    }
    this.type = type;
    this.name = name;
  }

  // get parameters
  public byte getCode( )
  {
    return code;
  }
  public String getType( )
  {
    return type;
  }
  public String getName( )
  {
    return name;
  }

  // get text representation
  public String toString( )
  {
    String codeStr = "unknown";
    switch( code )
    {
      case INSTR_STR_INF_BEGIN: codeStr = "begin"; break;
      case INSTR_STR_INF_END: codeStr = "end"; break;
      case INSTR_STR_INF_MIDDLE: codeStr = "middle"; break;
    }
    return "!strinf " + codeStr + " " + type + (name != null ? " " + name : "") + "\n";
  }

  // duplicate this instruction
  public Instr duplicate( )
  {
    return new InstrStrInf( code, type, name );
  }
} // public class InstrStrInf
