// Generated by Bisonc++ V2.09.03 on Thu, 27 Feb 2014 22:52:19 +0100

// $insert class.ih
#include "Parser.ih"

// The FIRST element of SR arrays shown below uses `d_type', defining the
// state's type, and `d_lastIdx' containing the last element's index. If
// d_lastIdx contains the REQ_TOKEN bitflag (see below) then the state needs
// a token: if in this state d_token__ is _UNDETERMINED_, nextToken() will be
// called

// The LAST element of SR arrays uses `d_token' containing the last retrieved
// token to speed up the (linear) seach.  Except for the first element of SR
// arrays, the field `d_action' is used to determine what to do next. If
// positive, it represents the next state (used with SHIFT); if zero, it
// indicates `ACCEPT', if negative, -d_action represents the number of the
// rule to reduce to.

// `lookup()' tries to find d_token__ in the current SR array. If it fails, and
// there is no default reduction UNEXPECTED_TOKEN__ is thrown, which is then
// caught by the error-recovery function.

// The error-recovery function will pop elements off the stack until a state
// having bit flag ERR_ITEM is found. This state has a transition on _error_
// which is applied. In this _error_ state, while the current token is not a
// proper continuation, new tokens are obtained by nextToken(). If such a
// token is found, error recovery is successful and the token is
// handled according to the error state's SR table and parsing continues.
// During error recovery semantic actions are ignored.

// A state flagged with the DEF_RED flag will perform a default
// reduction if no other continuations are available for the current token.

// The ACCEPT STATE never shows a default reduction: when it is reached the
// parser returns ACCEPT(). During the grammar
// analysis phase a default reduction may have been defined, but it is
// removed during the state-definition phase.

// So:
//      s_x[] = 
//      {
//                  [_field_1_]         [_field_2_]
//
// First element:   {state-type,        idx of last element},
// Other elements:  {required token,    action to perform},
//                                      ( < 0: reduce, 
//                                          0: ACCEPT,
//                                        > 0: next state)
// Last element:    {set to d_token__,    action to perform}
//      }

// When the --thread-safe option is specified, all static data are defined as
// const. If --thread-safe is not provided, the state-tables are not defined
// as const, since the lookup() function below will modify them


namespace // anonymous
{
    char const author[] = "Frank B. Brokken (f.b.brokken@rug.nl)";

    enum 
    {
        STACK_EXPANSION = 5     // size to expand the state-stack with when
                                // full
    };

    enum ReservedTokens
    {
        PARSE_ACCEPT     = 0,   // `ACCEPT' TRANSITION
        _UNDETERMINED_   = -2,
        _EOF_            = -1,
        _error_          = 256
    };
    enum StateType       // modify statetype/data.cc when this enum changes
    {
        NORMAL,
        ERR_ITEM,
        REQ_TOKEN,
        ERR_REQ,    // ERR_ITEM | REQ_TOKEN
        DEF_RED,    // state having default reduction
        ERR_DEF,    // ERR_ITEM | DEF_RED
        REQ_DEF,    // REQ_TOKEN | DEF_RED
        ERR_REQ_DEF // ERR_ITEM | REQ_TOKEN | DEF_RED
    };    
    struct PI__     // Production Info
    {
        size_t d_nonTerm; // identification number of this production's
                            // non-terminal 
        size_t d_size;    // number of elements in this production 
    };

    struct SR__     // Shift Reduce info, see its description above
    {
        union
        {
            int _field_1_;      // initializer, allowing initializations 
                                // of the SR s_[] arrays
            int d_type;
            int d_token;
        };
        union
        {
            int _field_2_;

            int d_lastIdx;          // if negative, the state uses SHIFT
            int d_action;           // may be negative (reduce), 
                                    // postive (shift), or 0 (accept)
            size_t d_errorState;    // used with Error states
        };
    };

    // $insert staticdata
    
// Productions Info Records:
PI__ const s_productionInfo[] = 
{
     {0, 0}, // not used: reduction values are negative
     {269, 2}, // 1: start ('\x0a') ->  line '\x0a'
     {269, 3}, // 2: start ('\x0a') ->  start line '\x0a'
     {270, 0}, // 3: line ->  <empty>
     {270, 2}, // 4: line (EQ_LINE) ->  EQ_LINE eq_defs
     {270, 2}, // 5: line (PARAM_LINE) ->  PARAM_LINE param_defs
     {270, 2}, // 6: line (VAR_LINE) ->  VAR_LINE var_defs
     {270, 2}, // 7: line (THRES_LINE) ->  THRES_LINE thres_defs
     {270, 2}, // 8: line (CONST_LINE) ->  CONST_LINE const_defs
     {270, 2}, // 9: line (INIT_LINE) ->  INIT_LINE init_defs
     {270, 1}, // 10: line (BA_LINE) ->  BA_LINE
     {276, 1}, // 11: init_defs ->  init_def
     {276, 3}, // 12: init_defs (';') ->  init_defs ';' init_def
     {277, 3}, // 13: init_def (',') ->  init_name ',' init_interval
     {278, 1}, // 14: init_name (NAME) ->  NAME
     {279, 3}, // 15: init_interval (',') ->  init_value ',' NUMBER
     {280, 1}, // 16: init_value (NUMBER) ->  NUMBER
     {275, 1}, // 17: const_defs ->  const_def
     {275, 3}, // 18: const_defs (';') ->  const_defs ';' const_def
     {281, 3}, // 19: const_def (',') ->  const_name ',' const_value
     {282, 1}, // 20: const_name (NAME) ->  NAME
     {283, 1}, // 21: const_value (NUMBER) ->  NUMBER
     {274, 3}, // 22: thres_defs (':') ->  thres_name ':' thres_values
     {284, 1}, // 23: thres_name (NAME) ->  NAME
     {285, 1}, // 24: thres_values (NUMBER) ->  NUMBER
     {285, 3}, // 25: thres_values (',') ->  thres_values ',' NUMBER
     {273, 1}, // 26: var_defs (NAME) ->  NAME
     {273, 3}, // 27: var_defs (',') ->  var_defs ',' NAME
     {272, 1}, // 28: param_defs ->  param_def
     {272, 3}, // 29: param_defs (';') ->  param_defs ';' param_def
     {286, 3}, // 30: param_def (',') ->  param_name ',' param_interval
     {288, 3}, // 31: param_interval (',') ->  param_value ',' NUMBER
     {287, 1}, // 32: param_name (NAME) ->  NAME
     {289, 1}, // 33: param_value (NUMBER) ->  NUMBER
     {271, 3}, // 34: eq_defs ('=') ->  eq_var '=' expr
     {290, 1}, // 35: eq_var (NAME) ->  NAME
     {292, 1}, // 36: ap (NUMBER) ->  NUMBER
     {292, 1}, // 37: ap (NAME) ->  NAME
     {292, 1}, // 38: ap (RAMP) ->  RAMP
     {292, 1}, // 39: ap (SIGM) ->  SIGM
     {292, 1}, // 40: ap (STEP) ->  STEP
     {291, 1}, // 41: expr ->  summation
     {291, 1}, // 42: expr ->  ap
     {293, 1}, // 43: summation ->  summant
     {293, 3}, // 44: summation ('+') ->  summation '+' summant
     {293, 3}, // 45: summation ('-') ->  summation '-' summant
     {294, 1}, // 46: summant ->  multiplication
     {294, 1}, // 47: summant ->  parenthesis
     {295, 1}, // 48: multiplication ->  multiple
     {295, 3}, // 49: multiplication ('*') ->  multiplication '*' multiple
     {297, 1}, // 50: multiple ->  ap
     {297, 1}, // 51: multiple ->  parenthesis
     {296, 3}, // 52: parenthesis ('(') ->  '(' expr ')'
     {296, 3}, // 53: parenthesis ('[') ->  '[' expr ']'
     {296, 4}, // 54: parenthesis ('(') ->  '(' '-' expr ')'
     {298, 1}, // 55: start_$ ->  start
};

// State info and SR__ transitions for each state.


SR__ s_0[] =
{
    { { REQ_DEF}, { 10} },              
    { {     269}, {  1} }, // start     
    { {     270}, {  2} }, // line      
    { {     259}, {  3} }, // EQ_LINE   
    { {     258}, {  4} }, // PARAM_LINE
    { {     257}, {  5} }, // VAR_LINE  
    { {     260}, {  6} }, // THRES_LINE
    { {     261}, {  7} }, // CONST_LINE
    { {     262}, {  8} }, // INIT_LINE 
    { {     263}, {  9} }, // BA_LINE   
    { {       0}, { -3} },              
};

SR__ s_1[] =
{
    { { REQ_DEF}, {           10} },              
    { {     270}, {           10} }, // line      
    { {     259}, {            3} }, // EQ_LINE   
    { {     258}, {            4} }, // PARAM_LINE
    { {     257}, {            5} }, // VAR_LINE  
    { {     260}, {            6} }, // THRES_LINE
    { {     261}, {            7} }, // CONST_LINE
    { {     262}, {            8} }, // INIT_LINE 
    { {     263}, {            9} }, // BA_LINE   
    { {   _EOF_}, { PARSE_ACCEPT} },              
    { {       0}, {           -3} },              
};

SR__ s_2[] =
{
    { { REQ_TOKEN}, {  2} },          
    { {        10}, { 11} }, // '\x0a'
    { {         0}, {  0} },          
};

SR__ s_3[] =
{
    { { REQ_TOKEN}, {  4} },           
    { {       271}, { 12} }, // eq_defs
    { {       290}, { 13} }, // eq_var 
    { {       264}, { 14} }, // NAME   
    { {         0}, {  0} },           
};

SR__ s_4[] =
{
    { { REQ_TOKEN}, {  5} },              
    { {       272}, { 15} }, // param_defs
    { {       286}, { 16} }, // param_def 
    { {       287}, { 17} }, // param_name
    { {       264}, { 18} }, // NAME      
    { {         0}, {  0} },              
};

SR__ s_5[] =
{
    { { REQ_TOKEN}, {  3} },            
    { {       273}, { 19} }, // var_defs
    { {       264}, { 20} }, // NAME    
    { {         0}, {  0} },            
};

SR__ s_6[] =
{
    { { REQ_TOKEN}, {  4} },              
    { {       274}, { 21} }, // thres_defs
    { {       284}, { 22} }, // thres_name
    { {       264}, { 23} }, // NAME      
    { {         0}, {  0} },              
};

SR__ s_7[] =
{
    { { REQ_TOKEN}, {  5} },              
    { {       275}, { 24} }, // const_defs
    { {       281}, { 25} }, // const_def 
    { {       282}, { 26} }, // const_name
    { {       264}, { 27} }, // NAME      
    { {         0}, {  0} },              
};

SR__ s_8[] =
{
    { { REQ_TOKEN}, {  5} },             
    { {       276}, { 28} }, // init_defs
    { {       277}, { 29} }, // init_def 
    { {       278}, { 30} }, // init_name
    { {       264}, { 31} }, // NAME     
    { {         0}, {  0} },             
};

SR__ s_9[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -10} }, 
};

SR__ s_10[] =
{
    { { REQ_TOKEN}, {  2} },          
    { {        10}, { 32} }, // '\x0a'
    { {         0}, {  0} },          
};

SR__ s_11[] =
{
    { { DEF_RED}, {  1} }, 
    { {       0}, { -1} }, 
};

SR__ s_12[] =
{
    { { DEF_RED}, {  1} }, 
    { {       0}, { -4} }, 
};

SR__ s_13[] =
{
    { { REQ_TOKEN}, {  2} },       
    { {        61}, { 33} }, // '='
    { {         0}, {  0} },       
};

SR__ s_14[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -35} }, 
};

SR__ s_15[] =
{
    { { REQ_DEF}, {  2} },       
    { {      59}, { 34} }, // ';'
    { {       0}, { -5} },       
};

SR__ s_16[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -28} }, 
};

SR__ s_17[] =
{
    { { REQ_TOKEN}, {  2} },       
    { {        44}, { 35} }, // ','
    { {         0}, {  0} },       
};

SR__ s_18[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -32} }, 
};

SR__ s_19[] =
{
    { { REQ_DEF}, {  2} },       
    { {      44}, { 36} }, // ','
    { {       0}, { -6} },       
};

SR__ s_20[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -26} }, 
};

SR__ s_21[] =
{
    { { DEF_RED}, {  1} }, 
    { {       0}, { -7} }, 
};

SR__ s_22[] =
{
    { { REQ_TOKEN}, {  2} },       
    { {        58}, { 37} }, // ':'
    { {         0}, {  0} },       
};

SR__ s_23[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -23} }, 
};

SR__ s_24[] =
{
    { { REQ_DEF}, {  2} },       
    { {      59}, { 38} }, // ';'
    { {       0}, { -8} },       
};

SR__ s_25[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -17} }, 
};

SR__ s_26[] =
{
    { { REQ_TOKEN}, {  2} },       
    { {        44}, { 39} }, // ','
    { {         0}, {  0} },       
};

SR__ s_27[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -20} }, 
};

SR__ s_28[] =
{
    { { REQ_DEF}, {  2} },       
    { {      59}, { 40} }, // ';'
    { {       0}, { -9} },       
};

SR__ s_29[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -11} }, 
};

SR__ s_30[] =
{
    { { REQ_TOKEN}, {  2} },       
    { {        44}, { 41} }, // ','
    { {         0}, {  0} },       
};

SR__ s_31[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -14} }, 
};

SR__ s_32[] =
{
    { { DEF_RED}, {  1} }, 
    { {       0}, { -2} }, 
};

SR__ s_33[] =
{
    { { REQ_TOKEN}, { 15} },                  
    { {       291}, { 42} }, // expr          
    { {       293}, { 43} }, // summation     
    { {       292}, { 44} }, // ap            
    { {       294}, { 45} }, // summant       
    { {       265}, { 46} }, // NUMBER        
    { {       264}, { 47} }, // NAME          
    { {       266}, { 48} }, // RAMP          
    { {       267}, { 49} }, // SIGM          
    { {       268}, { 50} }, // STEP          
    { {       295}, { 51} }, // multiplication
    { {       296}, { 52} }, // parenthesis   
    { {       297}, { 53} }, // multiple      
    { {        40}, { 54} }, // '('           
    { {        91}, { 55} }, // '['           
    { {         0}, {  0} },                  
};

SR__ s_34[] =
{
    { { REQ_TOKEN}, {  4} },              
    { {       286}, { 56} }, // param_def 
    { {       287}, { 17} }, // param_name
    { {       264}, { 18} }, // NAME      
    { {         0}, {  0} },              
};

SR__ s_35[] =
{
    { { REQ_TOKEN}, {  4} },                  
    { {       288}, { 57} }, // param_interval
    { {       289}, { 58} }, // param_value   
    { {       265}, { 59} }, // NUMBER        
    { {         0}, {  0} },                  
};

SR__ s_36[] =
{
    { { REQ_TOKEN}, {  2} },        
    { {       264}, { 60} }, // NAME
    { {         0}, {  0} },        
};

SR__ s_37[] =
{
    { { REQ_TOKEN}, {  3} },                
    { {       285}, { 61} }, // thres_values
    { {       265}, { 62} }, // NUMBER      
    { {         0}, {  0} },                
};

SR__ s_38[] =
{
    { { REQ_TOKEN}, {  4} },              
    { {       281}, { 63} }, // const_def 
    { {       282}, { 26} }, // const_name
    { {       264}, { 27} }, // NAME      
    { {         0}, {  0} },              
};

SR__ s_39[] =
{
    { { REQ_TOKEN}, {  3} },               
    { {       283}, { 64} }, // const_value
    { {       265}, { 65} }, // NUMBER     
    { {         0}, {  0} },               
};

SR__ s_40[] =
{
    { { REQ_TOKEN}, {  4} },             
    { {       277}, { 66} }, // init_def 
    { {       278}, { 30} }, // init_name
    { {       264}, { 31} }, // NAME     
    { {         0}, {  0} },             
};

SR__ s_41[] =
{
    { { REQ_TOKEN}, {  4} },                 
    { {       279}, { 67} }, // init_interval
    { {       280}, { 68} }, // init_value   
    { {       265}, { 69} }, // NUMBER       
    { {         0}, {  0} },                 
};

SR__ s_42[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -34} }, 
};

SR__ s_43[] =
{
    { { REQ_DEF}, {   3} },       
    { {      43}, {  70} }, // '+'
    { {      45}, {  71} }, // '-'
    { {       0}, { -41} },       
};

SR__ s_44[] =
{
    { { REQ_DEF}, {   4} },          
    { {      10}, { -42} }, // '\x0a'
    { {      41}, { -42} }, // ')'   
    { {      93}, { -42} }, // ']'   
    { {       0}, { -50} },          
};

SR__ s_45[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -43} }, 
};

SR__ s_46[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -36} }, 
};

SR__ s_47[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -37} }, 
};

SR__ s_48[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -38} }, 
};

SR__ s_49[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -39} }, 
};

SR__ s_50[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -40} }, 
};

SR__ s_51[] =
{
    { { REQ_DEF}, {   2} },       
    { {      42}, {  72} }, // '*'
    { {       0}, { -46} },       
};

SR__ s_52[] =
{
    { { REQ_DEF}, {   2} },       
    { {      42}, { -51} }, // '*'
    { {       0}, { -47} },       
};

SR__ s_53[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -48} }, 
};

SR__ s_54[] =
{
    { { REQ_TOKEN}, { 16} },                  
    { {       291}, { 73} }, // expr          
    { {        45}, { 74} }, // '-'           
    { {       293}, { 43} }, // summation     
    { {       292}, { 44} }, // ap            
    { {       294}, { 45} }, // summant       
    { {       265}, { 46} }, // NUMBER        
    { {       264}, { 47} }, // NAME          
    { {       266}, { 48} }, // RAMP          
    { {       267}, { 49} }, // SIGM          
    { {       268}, { 50} }, // STEP          
    { {       295}, { 51} }, // multiplication
    { {       296}, { 52} }, // parenthesis   
    { {       297}, { 53} }, // multiple      
    { {        40}, { 54} }, // '('           
    { {        91}, { 55} }, // '['           
    { {         0}, {  0} },                  
};

SR__ s_55[] =
{
    { { REQ_TOKEN}, { 15} },                  
    { {       291}, { 75} }, // expr          
    { {       293}, { 43} }, // summation     
    { {       292}, { 44} }, // ap            
    { {       294}, { 45} }, // summant       
    { {       265}, { 46} }, // NUMBER        
    { {       264}, { 47} }, // NAME          
    { {       266}, { 48} }, // RAMP          
    { {       267}, { 49} }, // SIGM          
    { {       268}, { 50} }, // STEP          
    { {       295}, { 51} }, // multiplication
    { {       296}, { 52} }, // parenthesis   
    { {       297}, { 53} }, // multiple      
    { {        40}, { 54} }, // '('           
    { {        91}, { 55} }, // '['           
    { {         0}, {  0} },                  
};

SR__ s_56[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -29} }, 
};

SR__ s_57[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -30} }, 
};

SR__ s_58[] =
{
    { { REQ_TOKEN}, {  2} },       
    { {        44}, { 76} }, // ','
    { {         0}, {  0} },       
};

SR__ s_59[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -33} }, 
};

SR__ s_60[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -27} }, 
};

SR__ s_61[] =
{
    { { REQ_DEF}, {   2} },       
    { {      44}, {  77} }, // ','
    { {       0}, { -22} },       
};

SR__ s_62[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -24} }, 
};

SR__ s_63[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -18} }, 
};

SR__ s_64[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -19} }, 
};

SR__ s_65[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -21} }, 
};

SR__ s_66[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -12} }, 
};

SR__ s_67[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -13} }, 
};

SR__ s_68[] =
{
    { { REQ_TOKEN}, {  2} },       
    { {        44}, { 78} }, // ','
    { {         0}, {  0} },       
};

SR__ s_69[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -16} }, 
};

SR__ s_70[] =
{
    { { REQ_TOKEN}, { 13} },                  
    { {       294}, { 79} }, // summant       
    { {       295}, { 51} }, // multiplication
    { {       296}, { 52} }, // parenthesis   
    { {       297}, { 53} }, // multiple      
    { {        40}, { 54} }, // '('           
    { {        91}, { 55} }, // '['           
    { {       292}, { 80} }, // ap            
    { {       265}, { 46} }, // NUMBER        
    { {       264}, { 47} }, // NAME          
    { {       266}, { 48} }, // RAMP          
    { {       267}, { 49} }, // SIGM          
    { {       268}, { 50} }, // STEP          
    { {         0}, {  0} },                  
};

SR__ s_71[] =
{
    { { REQ_TOKEN}, { 13} },                  
    { {       294}, { 81} }, // summant       
    { {       295}, { 51} }, // multiplication
    { {       296}, { 52} }, // parenthesis   
    { {       297}, { 53} }, // multiple      
    { {        40}, { 54} }, // '('           
    { {        91}, { 55} }, // '['           
    { {       292}, { 80} }, // ap            
    { {       265}, { 46} }, // NUMBER        
    { {       264}, { 47} }, // NAME          
    { {       266}, { 48} }, // RAMP          
    { {       267}, { 49} }, // SIGM          
    { {       268}, { 50} }, // STEP          
    { {         0}, {  0} },                  
};

SR__ s_72[] =
{
    { { REQ_TOKEN}, { 11} },               
    { {       297}, { 82} }, // multiple   
    { {       292}, { 80} }, // ap         
    { {       296}, { 83} }, // parenthesis
    { {       265}, { 46} }, // NUMBER     
    { {       264}, { 47} }, // NAME       
    { {       266}, { 48} }, // RAMP       
    { {       267}, { 49} }, // SIGM       
    { {       268}, { 50} }, // STEP       
    { {        40}, { 54} }, // '('        
    { {        91}, { 55} }, // '['        
    { {         0}, {  0} },               
};

SR__ s_73[] =
{
    { { REQ_TOKEN}, {  2} },       
    { {        41}, { 84} }, // ')'
    { {         0}, {  0} },       
};

SR__ s_74[] =
{
    { { REQ_TOKEN}, { 15} },                  
    { {       291}, { 85} }, // expr          
    { {       293}, { 43} }, // summation     
    { {       292}, { 44} }, // ap            
    { {       294}, { 45} }, // summant       
    { {       265}, { 46} }, // NUMBER        
    { {       264}, { 47} }, // NAME          
    { {       266}, { 48} }, // RAMP          
    { {       267}, { 49} }, // SIGM          
    { {       268}, { 50} }, // STEP          
    { {       295}, { 51} }, // multiplication
    { {       296}, { 52} }, // parenthesis   
    { {       297}, { 53} }, // multiple      
    { {        40}, { 54} }, // '('           
    { {        91}, { 55} }, // '['           
    { {         0}, {  0} },                  
};

SR__ s_75[] =
{
    { { REQ_TOKEN}, {  2} },       
    { {        93}, { 86} }, // ']'
    { {         0}, {  0} },       
};

SR__ s_76[] =
{
    { { REQ_TOKEN}, {  2} },          
    { {       265}, { 87} }, // NUMBER
    { {         0}, {  0} },          
};

SR__ s_77[] =
{
    { { REQ_TOKEN}, {  2} },          
    { {       265}, { 88} }, // NUMBER
    { {         0}, {  0} },          
};

SR__ s_78[] =
{
    { { REQ_TOKEN}, {  2} },          
    { {       265}, { 89} }, // NUMBER
    { {         0}, {  0} },          
};

SR__ s_79[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -44} }, 
};

SR__ s_80[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -50} }, 
};

SR__ s_81[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -45} }, 
};

SR__ s_82[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -49} }, 
};

SR__ s_83[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -51} }, 
};

SR__ s_84[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -52} }, 
};

SR__ s_85[] =
{
    { { REQ_TOKEN}, {  2} },       
    { {        41}, { 90} }, // ')'
    { {         0}, {  0} },       
};

SR__ s_86[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -53} }, 
};

SR__ s_87[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -31} }, 
};

SR__ s_88[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -25} }, 
};

SR__ s_89[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -15} }, 
};

SR__ s_90[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -54} }, 
};


// State array:
SR__ *s_state[] =
{
  s_0,  s_1,  s_2,  s_3,  s_4,  s_5,  s_6,  s_7,  s_8,  s_9,
  s_10,  s_11,  s_12,  s_13,  s_14,  s_15,  s_16,  s_17,  s_18,  s_19,
  s_20,  s_21,  s_22,  s_23,  s_24,  s_25,  s_26,  s_27,  s_28,  s_29,
  s_30,  s_31,  s_32,  s_33,  s_34,  s_35,  s_36,  s_37,  s_38,  s_39,
  s_40,  s_41,  s_42,  s_43,  s_44,  s_45,  s_46,  s_47,  s_48,  s_49,
  s_50,  s_51,  s_52,  s_53,  s_54,  s_55,  s_56,  s_57,  s_58,  s_59,
  s_60,  s_61,  s_62,  s_63,  s_64,  s_65,  s_66,  s_67,  s_68,  s_69,
  s_70,  s_71,  s_72,  s_73,  s_74,  s_75,  s_76,  s_77,  s_78,  s_79,
  s_80,  s_81,  s_82,  s_83,  s_84,  s_85,  s_86,  s_87,  s_88,  s_89,
  s_90,
};

} // anonymous namespace ends



// If the parsing function call uses arguments, then provide an overloaded
// function.  The code below doesn't rely on parameters, so no arguments are
// required.  Furthermore, parse uses a function try block to allow us to do
// ACCEPT and ABORT from anywhere, even from within members called by actions,
// simply throwing the appropriate exceptions.

ParserBase::ParserBase()
:
    d_stackIdx__(-1),
    // $insert debuginit
    d_debug__(false),
    d_nErrors__(0),
    // $insert requiredtokens
    d_requiredTokens__(0),
    d_acceptedTokens__(d_requiredTokens__),
    d_token__(_UNDETERMINED_),
    d_nextToken__(_UNDETERMINED_)
{}


void ParserBase::clearin()
{
    d_token__ = d_nextToken__ = _UNDETERMINED_;
}

void ParserBase::push__(size_t state)
{
    if (static_cast<size_t>(d_stackIdx__ + 1) == d_stateStack__.size())
    {
        size_t newSize = d_stackIdx__ + STACK_EXPANSION;
        d_stateStack__.resize(newSize);
        d_valueStack__.resize(newSize);
    }
    ++d_stackIdx__;
    d_stateStack__[d_stackIdx__] = d_state__ = state;
    *(d_vsp__ = &d_valueStack__[d_stackIdx__]) = d_val__;
}

void ParserBase::popToken__()
{
    d_token__ = d_nextToken__;

    d_val__ = d_nextVal__;
    d_nextVal__ = STYPE__();

    d_nextToken__ = _UNDETERMINED_;
}
     
void ParserBase::pushToken__(int token)
{
    d_nextToken__ = d_token__;
    d_nextVal__ = d_val__;
    d_token__ = token;
}
     
void ParserBase::pop__(size_t count)
{
    if (d_stackIdx__ < static_cast<int>(count))
    {
        ABORT();
    }

    d_stackIdx__ -= count;
    d_state__ = d_stateStack__[d_stackIdx__];
    d_vsp__ = &d_valueStack__[d_stackIdx__];
}

inline size_t ParserBase::top__() const
{
    return d_stateStack__[d_stackIdx__];
}

void Parser::executeAction(int production)
{
    if (d_token__ != _UNDETERMINED_)
        pushToken__(d_token__);     // save an already available token

                                    // save default non-nested block $$
    if (int size = s_productionInfo[production].d_size)
        d_val__ = d_vsp__[1 - size];

    switch (production)
    {
        // $insert actioncases
        
        case 1:
        {
         line_num++;
         d_scanner.column_num = 1;
         }
        break;

        case 2:
        {
         line_num++;
         d_scanner.column_num = 1;
         }
        break;

        case 10:
        {
         std::string ba = d_scanner.matched().substr(d_scanner.matched().find_first_not_of(" \t",3));
         std::cout << ba << std::endl;
         }
        break;

        case 13:
        { std::cout << '\n'; }
        break;

        case 14:
        { std::cout << "Init:" << d_scanner.matched() << ":";}
        break;

        case 15:
        { std::cout << '-' << d_scanner.matched();}
        break;

        case 16:
        { std::cout << d_scanner.matched();}
        break;

        case 20:
        { std::cout << d_scanner.matched() << ":";}
        break;

        case 21:
        { std::cout << d_scanner.matched() << std::endl;}
        break;

        case 22:
        {std::cout << "\n";}
        break;

        case 23:
        { std::cout << d_scanner.matched() << ":";}
        break;

        case 24:
        { std::cout << d_scanner.matched();}
        break;

        case 25:
        { std::cout << "," << d_scanner.matched();}
        break;

        case 26:
        { std::cout << d_scanner.matched() << ',';}
        break;

        case 27:
        { std::cout << d_scanner.matched() << std::endl;}
        break;

        case 30:
        {std::cout << "\n";}
        break;

        case 31:
        { std::cout << ',' << d_scanner.matched();}
        break;

        case 32:
        { std::cout << d_scanner.matched() << ":";}
        break;

        case 33:
        { std::cout << d_scanner.matched();}
        break;

        case 34:
        { std::cout << "-------END-EQ-------\n"; }
        break;

        case 35:
        { std::cout << "v_eq\t" << d_scanner.matched() << std::endl;}
        break;

        case 36:
        { std::cout << "c\t" << d_scanner.matched() << std::endl;
         storage.constant.push_back(stod(d_scanner.matched())); }
        break;

        case 37:
        { std::cout << "v\t" << d_scanner.matched() << std::endl;
         storage.var.push_back(d_scanner.matched()); }
        break;

        case 38:
        { std::cout << "r\t" << d_scanner.matched() << std::endl;
         storage.ramp.push_back(d_scanner.matched()); }
        break;

        case 39:
        { std::cout << "s\t" << d_scanner.matched() << std::endl;
         storage.sigm.push_back(d_scanner.matched()); }
        break;

        case 40:
        { std::cout << "h\t" << d_scanner.matched() << std::endl;
         storage.step.push_back(d_scanner.matched()); }
        break;

        case 41:
        { std::cout << "expr -> summation\n";}
        break;

        case 42:
        { std::cout << "expr -> ap\n";}
        break;

        case 43:
        { std::cout << "summation -> summant\n";}
        break;

        case 44:
        { std::cout << "summation -> summation + summant\n";}
        break;

        case 45:
        { std::cout << "summation -> summation - summant\n";}
        break;

        case 46:
        { std::cout << "summant -> multiplication\n";}
        break;

        case 47:
        { std::cout << "summant -> parenthesis\n";}
        break;

        case 48:
        { std::cout << "multiplication -> multiple\n";}
        break;

        case 49:
        { std::cout << "multiplication -> multiplication * multiple\n";}
        break;

        case 50:
        { std::cout << "multiple -> ap\n";}
        break;

        case 51:
        { std::cout << "multiple -> parenthesis\n";}
        break;

        case 52:
        { std::cout << "parenthesis -> ( expr )\n";}
        break;

        case 53:
        { std::cout << "parenthesis -> [ expr ]\n";}
        break;

        case 54:
        { std::cout << "parenthesis -> ( -expr )\n";}
        break;

    }
}

inline void ParserBase::reduce__(PI__ const &pi)
{
    d_token__ = pi.d_nonTerm;
    pop__(pi.d_size);

}

// If d_token__ is _UNDETERMINED_ then if d_nextToken__ is _UNDETERMINED_ another
// token is obtained from lex(). Then d_nextToken__ is assigned to d_token__.
void Parser::nextToken()
{
    if (d_token__ != _UNDETERMINED_)        // no need for a token: got one
        return;                             // already

    if (d_nextToken__ != _UNDETERMINED_)
    {
        popToken__();                       // consume pending token
    }
    else
    {
        ++d_acceptedTokens__;               // accept another token (see
                                            // errorRecover())
        d_token__ = lex();
        if (d_token__ <= 0)
            d_token__ = _EOF_;
    }
    print();
}

// if the final transition is negative, then we should reduce by the rule
// given by its positive value. Note that the `recovery' parameter is only
// used with the --debug option
int Parser::lookup(bool recovery)
{
    // $insert threading
    SR__ *sr = s_state[d_state__];        // get the appropriate state-table
    int lastIdx = sr->d_lastIdx;        // sentinel-index in the SR__ array

    SR__ *lastElementPtr = sr + lastIdx;
    SR__ *elementPtr = sr + 1;            // start the search at s_xx[1]

    lastElementPtr->d_token = d_token__;// set search-token

    while (elementPtr->d_token != d_token__)
        ++elementPtr;

    if (elementPtr == lastElementPtr)   // reached the last element
    {
        if (elementPtr->d_action < 0)   // default reduction
        {
            return elementPtr->d_action;                
        }

        // No default reduction, so token not found, so error.
        throw UNEXPECTED_TOKEN__;
    }

    // not at the last element: inspect the nature of the action
    // (< 0: reduce, 0: ACCEPT, > 0: shift)

    int action = elementPtr->d_action;


    return action;
}

    // When an error has occurred, pop elements off the stack until the top
    // state has an error-item. If none is found, the default recovery
    // mode (which is to abort) is activated. 
    //
    // If EOF is encountered without being appropriate for the current state,
    // then the error recovery will fall back to the default recovery mode.
    // (i.e., parsing terminates)
void Parser::errorRecovery()
try
{
    if (d_acceptedTokens__ >= d_requiredTokens__)// only generate an error-
    {                                           // message if enough tokens 
        ++d_nErrors__;                          // were accepted. Otherwise
        error("Syntax error");                  // simply skip input

    }


    // get the error state
    while (not (s_state[top__()][0].d_type & ERR_ITEM))
    {
        pop__();
    }

    // In the error state, lookup a token allowing us to proceed.
    // Continuation may be possible following multiple reductions,
    // but eventuall a shift will be used, requiring the retrieval of
    // a terminal token. If a retrieved token doesn't match, the catch below 
    // will ensure the next token is requested in the while(true) block
    // implemented below:

    int lastToken = d_token__;                  // give the unexpected token a
                                                // chance to be processed
                                                // again.

    pushToken__(_error_);                       // specify _error_ as next token
    push__(lookup(true));                       // push the error state

    d_token__ = lastToken;                      // reactivate the unexpected
                                                // token (we're now in an
                                                // ERROR state).

    bool gotToken = true;                       // the next token is a terminal

    while (true)
    {
        try
        {
            if (s_state[d_state__]->d_type & REQ_TOKEN)
            {
                gotToken = d_token__ == _UNDETERMINED_;
                nextToken();                    // obtain next token
            }
            
            int action = lookup(true);

            if (action > 0)                 // push a new state
            {
                push__(action);
                popToken__();

                if (gotToken)
                {

                    d_acceptedTokens__ = 0;
                    return;
                }
            }
            else if (action < 0)
            {
                // no actions executed on recovery but save an already 
                // available token:
                if (d_token__ != _UNDETERMINED_)
                    pushToken__(d_token__);
 
                                            // next token is the rule's LHS
                reduce__(s_productionInfo[-action]); 
            }
            else
                ABORT();                    // abort when accepting during
                                            // error recovery
        }
        catch (...)
        {
            if (d_token__ == _EOF_)
                ABORT();                    // saw inappropriate _EOF_
                      
            popToken__();                   // failing token now skipped
        }
    }
}
catch (ErrorRecovery__)       // This is: DEFAULT_RECOVERY_MODE
{
    ABORT();
}

    // The parsing algorithm:
    // Initially, state 0 is pushed on the stack, and d_token__ as well as
    // d_nextToken__ are initialized to _UNDETERMINED_. 
    //
    // Then, in an eternal loop:
    //
    //  1. If a state does not have REQ_TOKEN no token is assigned to
    //     d_token__. If the state has REQ_TOKEN, nextToken() is called to
    //      determine d_nextToken__ and d_token__ is set to
    //     d_nextToken__. nextToken() will not call lex() unless d_nextToken__ is 
    //     _UNDETERMINED_. 
    //
    //  2. lookup() is called: 
    //     d_token__ is stored in the final element's d_token field of the
    //     state's SR_ array. 
    //
    //  3. The current token is looked up in the state's SR_ array
    //
    //  4. Depending on the result of the lookup() function the next state is
    //     shifted on the parser's stack, a reduction by some rule is applied,
    //     or the parsing function returns ACCEPT(). When a reduction is
    //     called for, any action that may have been defined for that
    //     reduction is executed.
    //
    //  5. An error occurs if d_token__ is not found, and the state has no
    //     default reduction. Error handling was described at the top of this
    //     file.

int Parser::parse()
try 
{
    push__(0);                              // initial state
    clearin();                              // clear the tokens.

    while (true)
    {
        try
        {
            if (s_state[d_state__]->d_type & REQ_TOKEN)
                nextToken();                // obtain next token


            int action = lookup(false);     // lookup d_token__ in d_state__

            if (action > 0)                 // SHIFT: push a new state
            {
                push__(action);
                popToken__();               // token processed
            }
            else if (action < 0)            // REDUCE: execute and pop.
            {
                executeAction(-action);
                                            // next token is the rule's LHS
                reduce__(s_productionInfo[-action]); 
            }
            else 
                ACCEPT();
        }
        catch (ErrorRecovery__)
        {
            errorRecovery();
        }
    }
}
catch (Return__ retValue)
{
    return retValue;
}

