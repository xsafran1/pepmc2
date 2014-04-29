/* NIPS C - New Implementation of Promela Semantics Compiler
 * promela lexer package
 * Copyright (C) 2004-2005: Peter Eisentraut <peter_e@gmx.net>
 *                          Gustavo Quiros <gustavo.quiros@rwth-aachen.de>
 *                          Michael Rohrbach <m.rohrbach00@gmx.de>
 *                          Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                          Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package lexer;

import parser.promela.lexer.Lexer;
import parser.promela.lexer.Lexer.State;
import parser.promela.node.*;

public class PromelaLexer extends Lexer {
	private int count, comment_count;
	private TTSourceCodeBrace sourceCodeBrace;
	private TTSourceCodeBracket sourceCodeBracket;
	private TTStringCModeBraces stringCModeBraces;
        private TTStringCModeBrackets stringCModeBrackets;
	private TTComment comment;
	private TTCommentline commentline;
	private TTString string;
	private TTCommentlineCModeBraces commentlineCModeBraces;
        private TTCommentlineCModeBrackets commentlineCModeBrackets;
	private TTCommentCModeBraces commentCModeBraces;
        private TTCommentCModeBrackets commentCModeBrackets;
	private StringBuffer text, string_text, comment_text;

	// constructor
	public PromelaLexer(java.io.PushbackReader in){
		super(in);
	}

	// filter function
	protected void filter(){
		if (state.equals(State.NORMAL)){
			//System.out.println("status: normal");
		}
		if (state.equals(State.COMMENT)){
			//System.out.println("status: comment");
                       	if (comment == null){        // comment starts
                                // get token
                                comment = (TTComment) token;
                                // start string buffer for comment content
                                comment_text = new StringBuffer(comment.getText());
                                comment_count = 1;
                                // continue scanning
                                token = null;
                        } else {                                                                // comment continues
                                comment_text.append(token.getText());
                                if (token instanceof TTComment){
                                        comment_count++;
                                }
                                if (token instanceof TTCommentEnd){
                                        comment_count--;
                                }
                                if (comment_count != 0){
                                        token = null;
                                } else {
                                        comment.setText(comment_text.toString());
                                        token = comment;
                                        state = State.NORMAL;
                                        comment = null;
                                }
                        }
		}
                if (state.equals(State.COMMENTLINE)){
                        //System.out.println("status: commentline");
                        if (commentline == null){    // comment starts
                                // get token
                                commentline = (TTCommentline) token;
                                // start string buffer for comment content
                                comment_text = new StringBuffer(commentline.getText());
                                // continue scanning
                                token = null;
                        } else {                                                        // comment continues
                                comment_text.append(token.getText());
                                if (token instanceof TTCommentlineEnd){
                                        commentline.setText(comment_text.toString());
                                        token = commentline;
                                        state = State.NORMAL;
                                        commentline = null;
                                } else {
                                        token = null;
                                }
                        }
                }
		if (state.equals(State.C_MODE_WAITING)){
			//System.out.println("status: c_mode_waiting");
		}
                if (state.equals(State.C_MODE_BRACKETS_COMMENT)){
                        //System.out.println("status: c_mode_braces_comment");
                        if (text == null)                                       // code inly reachable from C_MODE_BRACKETS
                                System.out.println("test == null in C_MODE_BRACKETS_COMMENT");
                        if (commentCModeBrackets == null){        // comment starts
                                // get token
                                commentCModeBrackets = (TTCommentCModeBrackets) token;
                                // start string buffer for comment content
                                comment_text = new StringBuffer(commentCModeBrackets.getText());
                                comment_count = 1;
                                // continue scanning
                                token = null;
                        } else {                                                                // comment continues
                                comment_text.append(token.getText());
                                if (token instanceof TTCommentCModeBrackets){
                                        comment_count++;
                                }
                                if (token instanceof TTCModeCommentEnd){
                                        comment_count--;
                                }
                                if (comment_count != 0){
                                        token = null;
                                } else {
                                        commentCModeBrackets.setText(comment_text.toString());
                                        token = commentCModeBrackets;
                                        state = State.C_MODE_BRACKETS;
                                        commentCModeBraces = null;
                                }
                        }
                }
		if (state.equals(State.C_MODE_BRACES_COMMENT)){
			//System.out.println("status: c_mode_braces_comment");
			if (text == null)					// code inly reachable from C_MODE_BRACES
				System.out.println("test == null in C_MODE_BRACES_COMMENT");
			if (commentCModeBraces == null){	// comment starts
				// get token
				commentCModeBraces = (TTCommentCModeBraces) token;
				// start string buffer for comment content
				comment_text = new StringBuffer(commentCModeBraces.getText());
				comment_count = 1;
				// continue scanning
				token = null;
			} else {								// comment continues
				comment_text.append(token.getText());
				if (token instanceof TTCommentCModeBraces){
					comment_count++;
				}
				if (token instanceof TTCModeCommentEnd){
					comment_count--;
				}
				if (comment_count != 0){
					token = null;
				} else {
					commentCModeBraces.setText(comment_text.toString());
					token = commentCModeBraces;
					state = State.C_MODE_BRACES;
					commentCModeBraces = null;
				}
			}
		}
		if (state.equals(State.C_MODE_BRACES_COMMENTLINE)){
			//System.out.println("status: c_mode_braces_commentline");
			//System.out.println("token: " + token.getText() + ", " + token.getClass().getName());
			if (text == null)					// code inly reachable from C_MODE_BRACES
				System.out.println("test == null in C_MODE_BRACES_COMMENTLINE");
			if (commentlineCModeBraces == null){	// comment starts
				// get token
				commentlineCModeBraces = (TTCommentlineCModeBraces) token;
				// start string buffer for comment content
				comment_text = new StringBuffer(commentlineCModeBraces.getText());
				// continue scanning
				token = null;
			} else {							// comment continues
				comment_text.append(token.getText());
				if (token instanceof TTCModeCommentlineEnd){
					commentlineCModeBraces.setText(comment_text.toString());
					token = commentlineCModeBraces;
					state = State.C_MODE_BRACES;
					commentlineCModeBraces = null;
				} else {
					token = null;
				}
			}
		}
                if (state.equals(State.C_MODE_BRACKETS_COMMENTLINE)){
                        //System.out.println("status: c_mode_brackets_commentline");
                        //System.out.println("token: " + token.getText() + ", " + token.getClass().getName());
                        if (text == null)                                       // code inly reachable from C_MODE_BRACES
                                System.out.println("test == null in C_MODE_BRACKETS_COMMENTLINE");
                        if (commentlineCModeBrackets == null){    // comment starts
                                // get token
                                commentlineCModeBrackets = (TTCommentlineCModeBrackets) token;
                                // start string buffer for comment content
                                comment_text = new StringBuffer(commentlineCModeBrackets.getText());
                                // continue scanning
                                token = null;
                        } else {                                                        // comment continues
                                comment_text.append(token.getText());
                                if (token instanceof TTCModeCommentlineEnd){
                                        commentlineCModeBrackets.setText(comment_text.toString());
                                        token = commentlineCModeBrackets;
                                        state = State.C_MODE_BRACKETS;
                                        commentlineCModeBraces = null;
                                } else {
                                        token = null;
                                }
                        }
                }
                if (state.equals(State.STRING)){
			//System.out.println("STRING mode");
                        if (string == null){         // string starts
                                // get token
                                string = (TTString) token;
                                // start string buffer for string content
                                string_text = new StringBuffer(string.getText());
                                // continue scanning
                                token = null;
                        } else  {                                                       // string continues
                                string_text.append(token.getText());
                                if (token instanceof TTString){
                                        // give token back and switch to c_mode_braces
                                        string.setText(string_text.toString());
                                        token = string;
                                        state = State.NORMAL;
                                        string = null;
                                } else {
                                        token = null;
                                }
                        }
                }
		if (state.equals(State.C_MODE_BRACES_STRING)){
			if (text == null) 					// code only reachable from C_MODE_BRACES
				System.out.println("test == null in C_MODE_BRACES_STRING");
			if (stringCModeBraces == null){ 	// string starts
				// get token
				stringCModeBraces = (TTStringCModeBraces) token;
				// start string buffer for string content
				string_text = new StringBuffer(stringCModeBraces.getText());
				// continue scanning
				token = null;
			} else  { 							// string continues
				string_text.append(token.getText());
				if (token instanceof TTStringCModeBraces){
					// give token back and switch to c_mode_braces
					stringCModeBraces.setText(string_text.toString());
					token = stringCModeBraces;
					state = State.C_MODE_BRACES;
					stringCModeBraces = null;
				} else {
					token = null;
				}
			}
		}
                if (state.equals(State.C_MODE_BRACKETS_STRING)){
                        if (text == null)                                       // code only reachable from C_MODE_BRACKETS
                                System.out.println("test == null in C_MODE_BRACKETS_STRING");
                        if (stringCModeBrackets == null){         // string starts
                                // get token
                                stringCModeBrackets = (TTStringCModeBrackets) token;
                                // start string buffer for string content
                                string_text = new StringBuffer(stringCModeBrackets.getText());
                                // continue scanning
                                token = null;
                        } else  {                                                       // string continues
                                string_text.append(token.getText());
                                if (token instanceof TTStringCModeBrackets){
                                        // give token back and switch to c_mode_braces
                                        stringCModeBrackets.setText(string_text.toString());
                                        token = stringCModeBrackets;
                                        state = State.C_MODE_BRACKETS;
                                        stringCModeBraces = null;
                                } else {
                                        token = null;
                                }
                        }
                }
		if (state.equals(State.C_MODE_BRACES)){
			//System.out.println("status: c_mode_braces");
			if (sourceCodeBrace == null){
				// source code starts
				sourceCodeBrace = (TTSourceCodeBrace) token;
				// start StringBuffer
				text = new StringBuffer(sourceCodeBrace.getText());
				// just read a {
				count = 1;
				token = null;
			} else {
				// append token text
				text.append(token.getText());
				// source code continues
				if (token instanceof TTStringCModeBraces){
					//System.out.println("string recognized: " + token.getText());
				}
				if (token instanceof TTCommentlineCModeBraces){
					//System.out.println("commentline recognized: " + token.getText());
				}
				if (token instanceof TTCommentCModeBraces){
					//System.out.println("comment recognized: " + token.getText());
				}
				if (token instanceof TTSourceCodeBrace)
					count++;
				if (token instanceof TTSourceCodeBraceEnd)
					count--;
				if (count != 0)
					token = null;
				else {
					sourceCodeBrace.setText(text.toString());
					token = sourceCodeBrace;
					state = State.NORMAL;
					sourceCodeBrace = null;
				}
			}
		}
		if (state.equals(State.C_MODE_BRACKETS)){
                        //System.out.println("status: c_mode_brackets, token (" + token.getText() + ")");
                        if (sourceCodeBracket == null){
                                // source code starts
                                sourceCodeBracket = (TTSourceCodeBracket) token;
                                // start StringBuffer
                                text = new StringBuffer(sourceCodeBracket.getText());
                                // just read a {
                                count = 1;
                                token = null;
                        } else {
                                // append token text
                                text.append(token.getText());
                                // source code continues
                                if (token instanceof TTStringCModeBrackets){
                                        //System.out.println("string recognized: " + token.getText());
                                }
                                if (token instanceof TTCommentlineCModeBrackets){
                                        //System.out.println("commentline recognized: " + token.getText());
                                }
                                if (token instanceof TTCommentCModeBrackets){
                                        //System.out.println("comment recognized: " + token.getText());
                                }
                                if (token instanceof TTSourceCodeBracket)
                                        count++;
                                if (token instanceof TTSourceCodeBracketEnd)
                                        count--;
                                if (count != 0)
                                        token = null;
                                else {
                                        sourceCodeBracket.setText(text.toString());
                                        token = sourceCodeBracket;
                                        state = State.C_MODE_WAITING;
                                        sourceCodeBracket = null;
                                }
                        }
		}
		//System.out.println("filter: token text: " + token.getText());
	}
}		
