package Ast.Nodes;

public class Node_recv_poll extends Node_expr
{
  private String Attr_line;
  private String Attr_column;
  private String Attr_type;

  public Node_recv_poll( String Attr_line, String Attr_column, String Attr_type )
  {
    this.Attr_line = Attr_line;
    this.Attr_column = Attr_column;
    this.Attr_type = Attr_type;
  }

  public Node duplicate( )
  {
    return new Node_recv_poll( Attr_line, Attr_column, Attr_type );
  }

  public String getName( )
  {
    return "recv-poll";
  }

  public String getAttr_line( )
  {
    return Attr_line;
  }

  public String getAttr_column( )
  {
    return Attr_column;
  }

  public String getAttr_type( )
  {
    return Attr_type;
  }

  public String[][] getAttrs( )
  {
    String[][] attrs = new String[3][2];
    attrs[0][0] = "line";
    attrs[0][1] = Attr_line;
    attrs[1][0] = "column";
    attrs[1][1] = Attr_column;
    attrs[2][0] = "type";
    attrs[2][1] = Attr_type;
    return attrs;
  }

  public void accept( Visitor visitor )
  {
    visitor.visitNode_recv_poll( this );
  }
}
