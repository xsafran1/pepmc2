package Ast.Nodes;

public class Visitor
{
  protected Node parentNode = null; // used to make parent node available to children in acceptChildren

  public void visitNode( Node node )
  {
  }

  public void visitNode_expr( Node_expr node )
  {
    visitNode_sstmnt( node );
  }

  public void visitNode_sstmnt( Node_sstmnt node )
  {
    visitNode_stmnt( node );
  }

  public void visitNode_stmnt( Node_stmnt node )
  {
    visitNode_step( node );
  }

  public void visitNode_step( Node_step node )
  {
    visitNode( node );
  }

  public void visitNode_proc( Node_proc node )
  {
    visitNode( node );
  }

  public void visitNode_promela_ast( Node_promela_ast node )
  {
    visitNode( node );
  }

  public void visitNode_c_code( Node_c_code node )
  {
    visitNode( node );
  }

  public void visitNode_c_decl( Node_c_decl node )
  {
    visitNode( node );
  }

  public void visitNode_c_state( Node_c_state node )
  {
    visitNode( node );
  }

  public void visitNode_c_track( Node_c_track node )
  {
    visitNode( node );
  }

  public void visitNode_embedded_c( Node_embedded_c node )
  {
    visitNode( node );
  }

  public void visitNode_proctype( Node_proctype node )
  {
    visitNode_proc( node );
  }

  public void visitNode_args( Node_args node )
  {
    visitNode( node );
  }

  public void visitNode_init( Node_init node )
  {
    visitNode_proc( node );
  }

  public void visitNode_never( Node_never node )
  {
    visitNode_proc( node );
  }

  public void visitNode_trace( Node_trace node )
  {
    visitNode( node );
  }

  public void visitNode_notrace( Node_notrace node )
  {
    visitNode( node );
  }

  public void visitNode_utype( Node_utype node )
  {
    visitNode( node );
  }

  public void visitNode_mtype( Node_mtype node )
  {
    visitNode( node );
  }

  public void visitNode_mtype_name( Node_mtype_name node )
  {
    visitNode( node );
  }

  public void visitNode_inline_decl( Node_inline_decl node )
  {
    visitNode( node );
  }

  public void visitNode_inline_prms( Node_inline_prms node )
  {
    visitNode( node );
  }

  public void visitNode_inline_prm( Node_inline_prm node )
  {
    visitNode( node );
  }

  public void visitNode_decl( Node_decl node )
  {
    visitNode_step( node );
  }

  public void visitNode_inline_stmnt( Node_inline_stmnt node )
  {
    visitNode( node );
  }

  public void visitNode_typename( Node_typename node )
  {
    visitNode( node );
  }

  public void visitNode_enabler( Node_enabler node )
  {
    visitNode( node );
  }

  public void visitNode_unless( Node_unless node )
  {
    visitNode_stmnt( node );
  }

  public void visitNode_xr( Node_xr node )
  {
    visitNode_step( node );
  }

  public void visitNode_xs( Node_xs node )
  {
    visitNode_step( node );
  }

  public void visitNode_ivar( Node_ivar node )
  {
    visitNode( node );
  }

  public void visitNode_uivar( Node_uivar node )
  {
    visitNode( node );
  }

  public void visitNode_ch_init( Node_ch_init node )
  {
    visitNode( node );
  }

  public void visitNode_varref( Node_varref node )
  {
    visitNode_expr( node );
  }

  public void visitNode_array_index( Node_array_index node )
  {
    visitNode( node );
  }

  public void visitNode_send( Node_send node )
  {
    visitNode_sstmnt( node );
  }

  public void visitNode_receive( Node_receive node )
  {
    visitNode_sstmnt( node );
  }

  public void visitNode_underscore( Node_underscore node )
  {
    visitNode( node );
  }

  public void visitNode_eval( Node_eval node )
  {
    visitNode( node );
  }

  public void visitNode_receive_const( Node_receive_const node )
  {
    visitNode( node );
  }

  public void visitNode_recv_poll( Node_recv_poll node )
  {
    visitNode_expr( node );
  }

  public void visitNode_assign( Node_assign node )
  {
    visitNode_sstmnt( node );
  }

  public void visitNode_underscore_assign( Node_underscore_assign node )
  {
    visitNode_sstmnt( node );
  }

  public void visitNode_increment( Node_increment node )
  {
    visitNode_sstmnt( node );
  }

  public void visitNode_decrement( Node_decrement node )
  {
    visitNode_sstmnt( node );
  }

  public void visitNode_if( Node_if node )
  {
    visitNode_stmnt( node );
  }

  public void visitNode_do( Node_do node )
  {
    visitNode_stmnt( node );
  }

  public void visitNode_option( Node_option node )
  {
    visitNode( node );
  }

  public void visitNode_atomic( Node_atomic node )
  {
    visitNode_stmnt( node );
  }

  public void visitNode_d_step( Node_d_step node )
  {
    visitNode_stmnt( node );
  }

  public void visitNode_block( Node_block node )
  {
    visitNode_stmnt( node );
  }

  public void visitNode_else( Node_else node )
  {
    visitNode_stmnt( node );
  }

  public void visitNode_break( Node_break node )
  {
    visitNode_stmnt( node );
  }

  public void visitNode_goto( Node_goto node )
  {
    visitNode_stmnt( node );
  }

  public void visitNode_label( Node_label node )
  {
    visitNode_stmnt( node );
  }

  public void visitNode_printf( Node_printf node )
  {
    visitNode_sstmnt( node );
  }

  public void visitNode_assert( Node_assert node )
  {
    visitNode_sstmnt( node );
  }

  public void visitNode_c_expr( Node_c_expr node )
  {
    visitNode( node );
  }

  public void visitNode_c_assert( Node_c_assert node )
  {
    visitNode( node );
  }

  public void visitNode_add( Node_add node )
  {
    visitNode_expr( node );
  }

  public void visitNode_sub( Node_sub node )
  {
    visitNode_expr( node );
  }

  public void visitNode_mul( Node_mul node )
  {
    visitNode_expr( node );
  }

  public void visitNode_div( Node_div node )
  {
    visitNode_expr( node );
  }

  public void visitNode_mod( Node_mod node )
  {
    visitNode_expr( node );
  }

  public void visitNode_bit_and( Node_bit_and node )
  {
    visitNode_expr( node );
  }

  public void visitNode_bit_xor( Node_bit_xor node )
  {
    visitNode_expr( node );
  }

  public void visitNode_bit_or( Node_bit_or node )
  {
    visitNode_expr( node );
  }

  public void visitNode_gt( Node_gt node )
  {
    visitNode_expr( node );
  }

  public void visitNode_lt( Node_lt node )
  {
    visitNode_expr( node );
  }

  public void visitNode_gte( Node_gte node )
  {
    visitNode_expr( node );
  }

  public void visitNode_lte( Node_lte node )
  {
    visitNode_expr( node );
  }

  public void visitNode_eq( Node_eq node )
  {
    visitNode_expr( node );
  }

  public void visitNode_neq( Node_neq node )
  {
    visitNode_expr( node );
  }

  public void visitNode_ltlt( Node_ltlt node )
  {
    visitNode_expr( node );
  }

  public void visitNode_gtgt( Node_gtgt node )
  {
    visitNode_expr( node );
  }

  public void visitNode_and( Node_and node )
  {
    visitNode_expr( node );
  }

  public void visitNode_or( Node_or node )
  {
    visitNode_expr( node );
  }

  public void visitNode_tilde( Node_tilde node )
  {
    visitNode_expr( node );
  }

  public void visitNode_neg( Node_neg node )
  {
    visitNode_expr( node );
  }

  public void visitNode_excl( Node_excl node )
  {
    visitNode_expr( node );
  }

  public void visitNode_arrow_colon( Node_arrow_colon node )
  {
    visitNode_expr( node );
  }

  public void visitNode_len( Node_len node )
  {
    visitNode_expr( node );
  }

  public void visitNode_const_expr( Node_const_expr node )
  {
    visitNode_expr( node );
  }

  public void visitNode_timeout( Node_timeout node )
  {
    visitNode_expr( node );
  }

  public void visitNode_pid( Node_pid node )
  {
    visitNode_expr( node );
  }

  public void visitNode_nr_pr( Node_nr_pr node )
  {
    visitNode_expr( node );
  }

  public void visitNode_last( Node_last node )
  {
    visitNode_expr( node );
  }

  public void visitNode_np( Node_np node )
  {
    visitNode_expr( node );
  }

  public void visitNode_enabled( Node_enabled node )
  {
    visitNode_expr( node );
  }

  public void visitNode_pc_value( Node_pc_value node )
  {
    visitNode_expr( node );
  }

  public void visitNode_r_ref_label( Node_r_ref_label node )
  {
    visitNode_expr( node );
  }

  public void visitNode_r_ref_var( Node_r_ref_var node )
  {
    visitNode_expr( node );
  }

  public void visitNode_run( Node_run node )
  {
    visitNode_expr( node );
  }

  public void visitNode_chanop( Node_chanop node )
  {
    visitNode_expr( node );
  }

  public void acceptChildren( Node node )
  {
    Node[] children = node.getChildren( );
    for( int i = 0, j = 0; i < children.length; i++, j++ )
    {
      parentNode = node;
      children[i].accept( this );
    }
  }
}
