/* NIPS C - New Implementation of Promela Semantics Compiler
 * code generator package - instructions
 * Copyright (C) 2005: Stefan Schuermans <stefan@schuermans.info>
 *                     Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                     Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package CodeGen.Instr;

import java.io.*;

// an instruction sequence
public class InstrSeq extends DLList
{
  // create empty instruction sequence
  public InstrSeq( )
  {
  }

  // create instruction sequence with one instruction
  public InstrSeq( Instr instr )
  {
    append( instr );
  }

  // write string representation of instruction sequence to stream
  public void print( PrintStream stream )
  {
    for( Instr instr = (Instr)head( ); instr != null; instr = (Instr)instr.next( ) )
      stream.print( instr.toString( ) );
  }

  // get string representation of instruction sequence
  public String toString( )
  {
    String str = "";
    for( Instr instr = (Instr)head( ); instr != null; instr = (Instr)instr.next( ) )
      str += instr.toString( );
    return str;
  }

  // duplicate this instruction sequence
  public InstrSeq duplicate( )
  {
    // create a new instruction sequence and insert copies of all instructions into it
    InstrSeq seq = new InstrSeq( );
    for( Instr instr = (Instr)head( ); instr != null; instr = (Instr)instr.next( ) )
      seq.append( instr.duplicate( ) );
    return seq;
  }

  // get pointer to only real instruction in sequence
  // - return null if on ore multiple real instructions
  public InstrReal getSingleReal( )
  {
    InstrReal single = null;
    for( Instr instr = (Instr)head( ); instr != null; instr = (Instr)instr.next( ) )
    {
      if( instr instanceof InstrReal )
      {
        if( single == null )
          single = (InstrReal)instr;
        else
          return null;
      }
    }
    return single;
  }

  // get info instructions preceding first real instruction
  public InstrSeq getInfoPrefix( )
  {
    InstrSeq prefix = new InstrSeq( );
    for( Instr instr = (Instr)head( ); instr != null && (instr instanceof InstrInfo); instr = (Instr)instr.next( ) )
      prefix.append( instr.duplicate( ) );
    return prefix;
  }

  // get info instructions following last real instruction
  public InstrSeq getInfoSuffix( )
  {
    InstrSeq suffix = new InstrSeq( );
    for( Instr instr = (Instr)tail( ); instr != null && (instr instanceof InstrInfo); instr = (Instr)instr.prev( ) )
      suffix.prepend( instr.duplicate( ) );
    return suffix;
  }
} // public class InstrSeq
