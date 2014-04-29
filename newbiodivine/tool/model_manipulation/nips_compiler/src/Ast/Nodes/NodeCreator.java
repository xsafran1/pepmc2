package Ast.Nodes;

import org.jdom.*;

public class NodeCreator
{
  public static Node createNode( Element element )
  {
    String elName = element.getName( );
    if( elName.equals( "promela-ast" ) )
      return new Node_promela_ast(
                   element.getAttributeValue( "source" ) );
    if( elName.equals( "c-code" ) )
      return new Node_c_code(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "c-decl" ) )
      return new Node_c_decl(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "c-state" ) )
      return new Node_c_state(
                   element.getAttributeValue( "string1" ),
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ),
                   element.getAttributeValue( "string3" ),
                   element.getAttributeValue( "string2" ) );
    if( elName.equals( "c-track" ) )
      return new Node_c_track(
                   element.getAttributeValue( "string1" ),
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ),
                   element.getAttributeValue( "string2" ) );
    if( elName.equals( "embedded-c" ) )
      return new Node_embedded_c(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "proctype" ) )
      return new Node_proctype(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "name" ),
                   element.getAttributeValue( "priority" ),
                   element.getAttributeValue( "column" ),
                   element.getAttributeValue( "active" ) );
    if( elName.equals( "args" ) )
      return new Node_args(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "init" ) )
      return new Node_init(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "priority" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "never" ) )
      return new Node_never(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "trace" ) )
      return new Node_trace(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "notrace" ) )
      return new Node_notrace(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "utype" ) )
      return new Node_utype(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "name" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "mtype" ) )
      return new Node_mtype(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "mtype-name" ) )
      return new Node_mtype_name(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ),
                   element.getAttributeValue( "value" ) );
    if( elName.equals( "inline-decl" ) )
      return new Node_inline_decl(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "name" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "inline-prms" ) )
      return new Node_inline_prms(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "inline-prm" ) )
      return new Node_inline_prm(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "name" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "decl" ) )
      return new Node_decl(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ),
                   element.getAttributeValue( "typename" ),
                   element.getAttributeValue( "visible" ) );
    if( elName.equals( "inline-stmnt" ) )
      return new Node_inline_stmnt(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "name" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "typename" ) )
      return new Node_typename(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "name" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "enabler" ) )
      return new Node_enabler(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "unless" ) )
      return new Node_unless(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "xr" ) )
      return new Node_xr(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "xs" ) )
      return new Node_xs(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "ivar" ) )
      return new Node_ivar(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "array-size" ),
                   element.getAttributeValue( "name" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "uivar" ) )
      return new Node_uivar(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "array-size" ),
                   element.getAttributeValue( "name" ),
                   element.getAttributeValue( "column" ),
                   element.getAttributeValue( "bits" ) );
    if( elName.equals( "ch-init" ) )
      return new Node_ch_init(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "array-size" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "varref" ) )
      return new Node_varref(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "name" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "array-index" ) )
      return new Node_array_index(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "send" ) )
      return new Node_send(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ),
                   element.getAttributeValue( "type" ) );
    if( elName.equals( "receive" ) )
      return new Node_receive(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ),
                   element.getAttributeValue( "type" ) );
    if( elName.equals( "underscore" ) )
      return new Node_underscore(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "eval" ) )
      return new Node_eval(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "receive-const" ) )
      return new Node_receive_const(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ),
                   element.getAttributeValue( "value" ),
                   element.getAttributeValue( "neg" ) );
    if( elName.equals( "recv-poll" ) )
      return new Node_recv_poll(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ),
                   element.getAttributeValue( "type" ) );
    if( elName.equals( "assign" ) )
      return new Node_assign(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "underscore-assign" ) )
      return new Node_underscore_assign(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "increment" ) )
      return new Node_increment(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "decrement" ) )
      return new Node_decrement(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "if" ) )
      return new Node_if(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "do" ) )
      return new Node_do(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "option" ) )
      return new Node_option(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "atomic" ) )
      return new Node_atomic(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "d-step" ) )
      return new Node_d_step(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "block" ) )
      return new Node_block(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "else" ) )
      return new Node_else(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "break" ) )
      return new Node_break(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "goto" ) )
      return new Node_goto(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "name" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "label" ) )
      return new Node_label(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "name" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "printf" ) )
      return new Node_printf(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ),
                   element.getAttributeValue( "format" ) );
    if( elName.equals( "assert" ) )
      return new Node_assert(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "c-expr" ) )
      return new Node_c_expr(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "c-assert" ) )
      return new Node_c_assert(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "add" ) )
      return new Node_add(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "sub" ) )
      return new Node_sub(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "mul" ) )
      return new Node_mul(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "div" ) )
      return new Node_div(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "mod" ) )
      return new Node_mod(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "bit-and" ) )
      return new Node_bit_and(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "bit-xor" ) )
      return new Node_bit_xor(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "bit-or" ) )
      return new Node_bit_or(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "gt" ) )
      return new Node_gt(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "lt" ) )
      return new Node_lt(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "gte" ) )
      return new Node_gte(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "lte" ) )
      return new Node_lte(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "eq" ) )
      return new Node_eq(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "neq" ) )
      return new Node_neq(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "ltlt" ) )
      return new Node_ltlt(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "gtgt" ) )
      return new Node_gtgt(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "and" ) )
      return new Node_and(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "or" ) )
      return new Node_or(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "tilde" ) )
      return new Node_tilde(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "neg" ) )
      return new Node_neg(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "excl" ) )
      return new Node_excl(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "arrow-colon" ) )
      return new Node_arrow_colon(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "len" ) )
      return new Node_len(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "const-expr" ) )
      return new Node_const_expr(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ),
                   element.getAttributeValue( "value" ) );
    if( elName.equals( "timeout" ) )
      return new Node_timeout(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "pid" ) )
      return new Node_pid(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "nr_pr" ) )
      return new Node_nr_pr(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "last" ) )
      return new Node_last(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "np" ) )
      return new Node_np(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "enabled" ) )
      return new Node_enabled(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "pc-value" ) )
      return new Node_pc_value(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "r-ref-label" ) )
      return new Node_r_ref_label(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "proc" ),
                   element.getAttributeValue( "name" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "r-ref-var" ) )
      return new Node_r_ref_var(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "proc" ),
                   element.getAttributeValue( "name" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "run" ) )
      return new Node_run(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "name" ),
                   element.getAttributeValue( "priority" ),
                   element.getAttributeValue( "column" ) );
    if( elName.equals( "chanop" ) )
      return new Node_chanop(
                   element.getAttributeValue( "line" ),
                   element.getAttributeValue( "column" ),
                   element.getAttributeValue( "type" ) );
    throw new RuntimeException( "unknown AST node type \"" + elName + "\"" );
  }
}
