package Ast.Nodes;

public class Node_r_ref_label extends Node_expr
{
  private String Attr_line;
  private String Attr_proc;
  private String Attr_name;
  private String Attr_column;

  public Node_r_ref_label( String Attr_line, String Attr_proc, String Attr_name, String Attr_column )
  {
    this.Attr_line = Attr_line;
    this.Attr_proc = Attr_proc;
    this.Attr_name = Attr_name;
    this.Attr_column = Attr_column;
  }

  public Node duplicate( )
  {
    return new Node_r_ref_label( Attr_line, Attr_proc, Attr_name, Attr_column );
  }

  public String getName( )
  {
    return "r-ref-label";
  }

  public String getAttr_line( )
  {
    return Attr_line;
  }

  public String getAttr_proc( )
  {
    return Attr_proc;
  }

  public String getAttr_name( )
  {
    return Attr_name;
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
    attrs[1][0] = "proc";
    attrs[1][1] = Attr_proc;
    attrs[2][0] = "name";
    attrs[2][1] = Attr_name;
    attrs[3][0] = "column";
    attrs[3][1] = Attr_column;
    return attrs;
  }

  public void accept( Visitor visitor )
  {
    visitor.visitNode_r_ref_label( this );
  }
}
