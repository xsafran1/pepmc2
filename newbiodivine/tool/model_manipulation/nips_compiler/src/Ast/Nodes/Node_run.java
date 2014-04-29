package Ast.Nodes;

public class Node_run extends Node_expr
{
  private String Attr_line;
  private String Attr_name;
  private String Attr_priority;
  private String Attr_column;

  public Node_run( String Attr_line, String Attr_name, String Attr_priority, String Attr_column )
  {
    this.Attr_line = Attr_line;
    this.Attr_name = Attr_name;
    this.Attr_priority = Attr_priority;
    this.Attr_column = Attr_column;
  }

  public Node duplicate( )
  {
    return new Node_run( Attr_line, Attr_name, Attr_priority, Attr_column );
  }

  public String getName( )
  {
    return "run";
  }

  public String getAttr_line( )
  {
    return Attr_line;
  }

  public String getAttr_name( )
  {
    return Attr_name;
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
    String[][] attrs = new String[4][2];
    attrs[0][0] = "line";
    attrs[0][1] = Attr_line;
    attrs[1][0] = "name";
    attrs[1][1] = Attr_name;
    attrs[2][0] = "priority";
    attrs[2][1] = Attr_priority;
    attrs[3][0] = "column";
    attrs[3][1] = Attr_column;
    return attrs;
  }

  public void accept( Visitor visitor )
  {
    visitor.visitNode_run( this );
  }
}
