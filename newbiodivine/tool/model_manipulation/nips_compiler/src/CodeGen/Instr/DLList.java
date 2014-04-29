/* NIPS C - New Implementation of Promela Semantics Compiler
 * code generator package - instructions
 * Copyright (C) 2005: Stefan Schuermans <stefan@schuermans.info>
 *                     Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                     Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package CodeGen.Instr;

// a doubly linked list
public class DLList
{
  // head and tail of list
  private DLListEl head = null, tail = null;

  // get head of list
  public DLListEl head( )
  {
    return head;
  }

  // get tail of list
  public DLListEl tail( )
  {
    return tail;
  }

  // get length of list
  public int length( )
  {
    int len = 0;
    for( DLListEl el = head; el != null; el = el.next )
      len++;
    return len;
  }

  // append an element to this list
  public void append( DLListEl el )
  {
    if( head == null || tail == null ) // list empty
    {
      el.prev = null;
      el.next = null;
      head = el;
      tail = el;
    }
    else // list not empty
    {
      tail.next = el;
      el.prev = tail;
      el.next = null;
      tail = el;
    }
  }

  // append another list to this list
  public void append( DLList list )
  {
    if( list.head == null || list.tail == null ) // list to append is empty
      return;
    if( head == null || tail == null ) // list empty
    {
      head = list.head; // just use list to append as list
      tail = list.tail;
    }
    else // list not empty
    {
      tail.next = list.head; // append first list to end of second one
      list.head.prev = tail;
      tail = list.tail;
    }
    list.head = null; // remove elements from second list
    list.tail = null;
  }
  
  // prepend an element to this list
  public void prepend( DLListEl el )
  {
    if( head == null || tail == null ) // list empty
    {
      el.prev = null;
      el.next = null;
      head = el;
      tail = el;
    }
    else // list not empty
    {
      head.prev = el;
      el.prev = null;
      el.next = head;
      head = el;
    }
  }
} // public class DLList
