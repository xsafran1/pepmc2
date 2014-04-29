package Ast.Nodes;

public class Node_c_expr extends Node
{
  private String Attr_line;
  private String Attr_column;

  public Node_c_expr( String Attr_line, String Attr_column )
  {
    this.Attr_line = Attr_line;
    this.Attr_column = Attr_column;
  }

  public Node duplicate( )
  {
    return new Node_c_expr( Attr_line, Attr_column );
  }

  public String getName( )
  {
    return "c-expr";
  }

  public String getAttr_line( )
  {
    return Attr_line;
  }

  public String getAttr_column( )
  {
    return Attr_column;
  }

  public String[][] getAttrs( )
  {
    String[][] attrs = new String[2][2];
    attrs[0][0] = "line";
    attrs[0][1] = Attr_line;
    attrs[1][0] = "column";
    attrs[1][1] = Attr_column;
    return attrs;
  }

  public void accept( Visitor visitor )
  {
    visitor.visitNode_c_expr( this );
  }
}
