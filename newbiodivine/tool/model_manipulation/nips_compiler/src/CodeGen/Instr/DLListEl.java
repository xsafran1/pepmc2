/* NIPS C - New Implementation of Promela Semantics Compiler
 * code generator package - instructions
 * Copyright (C) 2005: Stefan Schuermans <stefan@schuermans.info>
 *                     Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                     Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package CodeGen.Instr;

// an element in a doubly linked list
public class DLListEl
{
  DLListEl next = null, prev = null; // pointers of doubly linked list

  // get next element
  public DLListEl next( )
  {
    return next;
  }

  // get previous element
  public DLListEl prev( )
  {
    return prev;
  }
} // public class DLListEl
