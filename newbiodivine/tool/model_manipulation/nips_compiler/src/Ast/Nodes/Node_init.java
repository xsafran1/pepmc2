package Ast.Nodes;

public class Node_init extends Node_proc
{
  private String Attr_line;
  private String Attr_priority;
  private String Attr_column;

  public Node_init( String Attr_line, String Attr_priority, String Attr_column )
  {
    this.Attr_line = Attr_line;
    this.Attr_priority = Attr_priority;
    this.Attr_column = Attr_column;
  }

  public Node duplicate( )
  {
    return new Node_init( Attr_line, Attr_priority, Attr_column );
  }

  public String getName( )
  {
    return "init";
  }

  public String getAttr_line( )
  {
    return Attr_line;
  }

  public String getAttr_priority( )
  {
    return Attr_priority;
  }

  public String getAttr_column( )
  {
    return Attr_column;
  }

  public String[][] getAttrs( )
  {
    String[][] attrs = new String[3][2];
    attrs[0][0] = "line";
    attrs[0][1] = Attr_line;
    attrs[1][0] = "priority";
    attrs[1][1] = Attr_priority;
    attrs[2][0] = "column";
    attrs[2][1] = Attr_column;
    return attrs;
  }

  public void accept( Visitor visitor )
  {
    visitor.visitNode_init( this );
  }
}
