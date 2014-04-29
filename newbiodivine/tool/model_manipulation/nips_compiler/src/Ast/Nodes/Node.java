package Ast.Nodes;

import StatSem.SymTab.*;

public abstract class Node
{
  private Node children[] = new Node[0];
  private Scope scope = null;

  public abstract Node duplicate( );

  public Node[] getChildren( )
  {
    return children;
  }

  public int getChildCnt( )
  {
    return children.length;
  }

  public Node getChild( int idx )
  {
    if( idx >= 0 && idx < children.length )
      return children[idx];
    else
      return null;
  }

  public Node getChild( String name )
  {
    for( int i = 0; i < children.length; i++ )
      if( children[i].getName( ).equals( name ) )
        return children[i];
    return null;
  }

  public void setChild( int idx, Node newChild )
  {
    if( idx >= 0 && idx < children.length )
      children[idx] = newChild;
  }

  public void addChild( Node newChild )
  {
    Node childrenNew[] = new Node[children.length + 1];
    for( int i = 0; i < children.length; i++ )
      childrenNew[i] = children[i];
    childrenNew[children.length] = newChild;
    children = childrenNew;
  }

  public abstract String getName( );

  public String getAttr_line( )
  {
    return null;
  }

  public String getAttr_column( )
  {
    return null;
  }

  public abstract String[][] getAttrs( );

  public Scope getScope( )
  {
    return scope;
  }

  public void setScope( Scope scope )
  {
    this.scope = scope;
  }

  public abstract void accept( Visitor visitor );
}
