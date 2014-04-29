package Ast.Nodes;

public class Node_printf extends Node_sstmnt
{
  private String Attr_line;
  private String Attr_column;
  private String Attr_format;

  public Node_printf( String Attr_line, String Attr_column, String Attr_format )
  {
    this.Attr_line = Attr_line;
    this.Attr_column = Attr_column;
    this.Attr_format = Attr_format;
  }

  public Node duplicate( )
  {
    return new Node_printf( Attr_line, Attr_column, Attr_format );
  }

  public String getName( )
  {
    return "printf";
  }

  public String getAttr_line( )
  {
    return Attr_line;
  }

  public String getAttr_column( )
  {
    return Attr_column;
  }

  public String getAttr_format( )
  {
    return Attr_format;
  }

  public String[][] getAttrs( )
  {
    String[][] attrs = new String[3][2];
    attrs[0][0] = "line";
    attrs[0][1] = Attr_line;
    attrs[1][0] = "column";
    attrs[1][1] = Attr_column;
    attrs[2][0] = "format";
    attrs[2][1] = Attr_format;
    return attrs;
  }

  public void accept( Visitor visitor )
  {
    visitor.visitNode_printf( this );
  }
}
