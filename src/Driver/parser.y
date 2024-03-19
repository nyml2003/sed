%skeleton "lalr1.cc"

%code requires {
    #include "ast_node_base.hpp"
    #include "ast_expression_base.hpp"
    #include "ast_expression_binary_expression.hpp"
    #include "ast_expression_unary_expression.hpp"
    #include "ast_expression_boolean.hpp"
    #include "ast_expression_float32.hpp"
    #include "ast_expression_identifier.hpp"
    #include "ast_expression_int32.hpp"
    #include "ast_expression_operator.hpp"
    #include "ast_node_block.hpp"
    #include "ast_node_break_statement.hpp"
    #include "ast_node_compilation_unit.hpp"
    #include "ast_node_continue_statement.hpp"
    #include "ast_node_declaration.hpp"
    #include "ast_node_definition.hpp"
    #include "ast_node_function_definition.hpp"
    #include "ast_node_if_statement.hpp"
    #include "ast_expression_initial_value.hpp"
    #include "ast_expression_left_value.hpp"
    #include "ast_node_return_statement.hpp"
    #include "ast_node_while_statement.hpp"
    #include "ast_node_expression_statement.hpp"
    #include "ast_node_assignment_statement.hpp"
    namespace Compiler::Core {
        class Driver;
    }
    using Driver = Compiler::Core::Driver;
}

%code {
    #include "Driver.hpp"
}

%language "c++"
%locations
%param { Driver &driver }

%define api.value.type variant
%define api.token.raw
%define api.token.constructor
%define api.token.prefix {TOKEN_}
%define parse.assert

%define parse.error detailed
%define parse.lac full
%define parse.trace

%type < Compiler::AST::Base* > CompUnit Decl FuncDef Block BlockItem Stmt Def
%type < std::vector< Compiler::AST::Base* > > DefList CompUnitContainer BlockItemList
%type < Compiler::AST::Expression::Base* > UnaryExp MulExp AddExp RelExp EqExp LAndExp LOrExp PrimaryExp Ident Number Exp Cond Lval InitVal
%type < std::vector< Compiler::AST::Expression::Base* > > DimList InitValList
%type < Compiler::AST::Expression::Operator > UNARYOP
%type < Compiler::AST::InnerType > Type
%token<std::string> IDENT
%token RETURN CONST
%token TYPE_INT TYPE_VOID TYPE_FLOAT
%token<std::int32_t> INT_CONST
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON COMMA LBRACKET RBRACKET
%token PLUS MINUS STAR SLASH PERCENT AND OR EQ NE LT GT LE GE NOT ASSIGN CONTINUE BREAK IF ELSE WHILE


%%
%start CompUnit;

CompUnit:
    CompUnitContainer { 
        auto compUnit = new Compiler::AST::CompilationUnit();
        compUnit->attach(std::move($1)); 
        driver.result = std::move(compUnit); 
    }
    ;

CompUnitContainer: 
      Decl { $$ = std::vector< Compiler::AST::Base* >(); $$.push_back($1); }
    | FuncDef { $$ = std::vector< Compiler::AST::Base* >(); $$.push_back($1); }
    | CompUnitContainer Decl { $$ = $1; $$.push_back($2); }
    | CompUnitContainer FuncDef { $$ = $1; $$.push_back($2); }
    ;

Decl : 
    Type DefList SEMICOLON { 
        $$ = new Compiler::AST::Declaration($1,$2);
    }
    | CONST Decl {
        $$ = $2;
        dynamic_cast< Compiler::AST::Declaration* >($$)->addDecorator(Compiler::AST::Decorator::CONSTANT);
    }
    ;

Type:
    TYPE_INT { $$ = Compiler::AST::InnerType::INT;}
    | TYPE_FLOAT { $$ = Compiler::AST::InnerType::FLOAT; }
    | TYPE_VOID { $$ = Compiler::AST::InnerType::VOID; }
    ;

Def:
    Lval ASSIGN InitVal { $$ = new Compiler::AST::Definition($1,$3); }
    | Lval { $$ = new Compiler::AST::Definition($1); }
    ;

InitVal:
    Exp { $$ = new Compiler::AST::Expression::InitialValue($1); }
    | LBRACE InitValList RBRACE { $$ = new Compiler::AST::Expression::InitialValue($2); }
    ;

InitValList:
    InitVal { $$ = std::vector< Compiler::AST::Expression::Base* >(); $$.push_back($1); }
    | InitValList COMMA InitVal { $$ = $1; $$.push_back($3); }
    ;

DefList:
    Def { $$ = std::vector< Compiler::AST::Base* >(); $$.push_back($1); }
    | DefList COMMA Def { $1.push_back($3); $$ = $1; }
    ;

FuncDef:
    Type Ident LPAREN RPAREN Block {
        $$ = new Compiler::AST::FunctionDefinition($1,$2,$5);
    }
    ;

Ident :
    IDENT { $$ = new Compiler::AST::Expression::Identifier($1); }
    ;

Block:
    LBRACE RBRACE { $$ = new Compiler::AST::Block(); }
    | LBRACE BlockItemList RBRACE { $$ = new Compiler::AST::Block(std::move($2)); }
    ;

BlockItemList:
    BlockItem { $$ = std::vector< Compiler::AST::Base* >(); $$.push_back($1); }
    | BlockItemList BlockItem { $$ = $1; $$.push_back($2); }
    ;

BlockItem:
    Decl { $$ = $1; }
    | Stmt { $$ = $1; }
    ;

Stmt:
    Lval ASSIGN Exp SEMICOLON { $$ = new Compiler::AST::AssignmentStatement($1,$3); }
    | Exp SEMICOLON { $$ = new Compiler::AST::ExpressionStatement($1); }
    | IF LPAREN Cond RPAREN Stmt ELSE Stmt { $$ = new Compiler::AST::IfStatement($3,$5,$7); }
    | IF LPAREN Cond RPAREN Stmt { $$ = new Compiler::AST::IfStatement($3,$5); }
    | WHILE LPAREN Cond RPAREN Stmt { $$ = new Compiler::AST::WhileStatement($3,$5); }
    | RETURN Exp SEMICOLON { $$ = new Compiler::AST::ReturnStatement($2); }
    | BREAK SEMICOLON { $$ = new Compiler::AST::BreakStatement(); }
    | CONTINUE SEMICOLON { $$ = new Compiler::AST::ContinueStatement(); }
    | Block { $$ = $1; }
    ;

Exp:
    AddExp { $$ = $1; }
    ;

Cond:
    LOrExp { $$ = $1; }
    ;

Lval: 
    Ident { $$ = new Compiler::AST::Expression::LeftValue($1); }
    | Ident DimList { $$ = new Compiler::AST::Expression::LeftValue($1,$2); }
    ;

DimList:
      LBRACKET RBRACKET { $$ = std::vector< Compiler::AST::Expression::Base* >(); $$.push_back(new Compiler::AST::Expression::Int32(0)); }
    | LBRACKET Exp RBRACKET { $$ = std::vector< Compiler::AST::Expression::Base* >(); $$.push_back($2); }
    | DimList LBRACKET RBRACKET { $$ = $1; $$.push_back(new Compiler::AST::Expression::Int32(0)); }
    | DimList LBRACKET Exp RBRACKET { $$ = $1; $$.push_back($3); }
    ;

PrimaryExp:
    Lval { $$ = $1;}
    | LPAREN Exp RPAREN { $$ = $2; }
    | Number { $$ = $1; }
    ;

Number:
    INT_CONST { $$ = new Compiler::AST::Expression::Int32($1); }
    ;

UNARYOP:
    MINUS { $$ = Compiler::AST::Expression::Operator::MINUS; }
    | NOT { $$ = Compiler::AST::Expression::Operator::NOT; }
    | PLUS { $$ = Compiler::AST::Expression::Operator::PLUS; }
    ;

UnaryExp:
    PrimaryExp { $$ = $1; }
    | UNARYOP UnaryExp {
        $$ = new Compiler::AST::Expression::UnaryExpression($1,$2);
    }
    ;

MulExp:
    UnaryExp { $$ = $1; }
    | MulExp STAR UnaryExp { 
        $$ = new Compiler::AST::Expression::BinaryExpression(Compiler::AST::Expression::Operator::MUL,$1,$3);
    }
    | MulExp SLASH UnaryExp { 
        $$ = new Compiler::AST::Expression::BinaryExpression(Compiler::AST::Expression::Operator::DIV,$1,$3);
    }
    | MulExp PERCENT UnaryExp { 
        $$ = new Compiler::AST::Expression::BinaryExpression(Compiler::AST::Expression::Operator::MOD,$1,$3);
    }
    ;

AddExp:
    MulExp { $$ = $1; }
    | AddExp PLUS MulExp { 
        $$ = new Compiler::AST::Expression::BinaryExpression(Compiler::AST::Expression::Operator::ADD,$1,$3);
    }
    | AddExp MINUS MulExp { 
        $$ = new Compiler::AST::Expression::BinaryExpression(Compiler::AST::Expression::Operator::SUB,$1,$3);
    }
    ;

RelExp:
    AddExp { $$ = $1; }
    | RelExp LT AddExp { 
        $$ = new Compiler::AST::Expression::BinaryExpression(Compiler::AST::Expression::Operator::LT,$1,$3);
    }
    | RelExp GT AddExp { 
        $$ = new Compiler::AST::Expression::BinaryExpression(Compiler::AST::Expression::Operator::GT,$1,$3);
    }
    | RelExp LE AddExp { 
        $$ = new Compiler::AST::Expression::BinaryExpression(Compiler::AST::Expression::Operator::LE,$1,$3);
    }
    | RelExp GE AddExp { 
        $$ = new Compiler::AST::Expression::BinaryExpression(Compiler::AST::Expression::Operator::GE,$1,$3);
    }
    ;

EqExp:
    RelExp { $$ = $1; }
    | EqExp EQ RelExp { 
        $$ = new Compiler::AST::Expression::BinaryExpression(Compiler::AST::Expression::Operator::EQ,$1,$3);
    }
    | EqExp NE RelExp { 
        $$ = new Compiler::AST::Expression::BinaryExpression(Compiler::AST::Expression::Operator::NE,$1,$3);
    }
    ;

LAndExp:
    EqExp { $$ = $1; }
    | LAndExp AND EqExp { 
        $$ = new Compiler::AST::Expression::BinaryExpression(Compiler::AST::Expression::Operator::AND,$1,$3);
    }

LOrExp:
    LAndExp { $$ = $1; }
    | LOrExp OR LAndExp { 
        $$ = new Compiler::AST::Expression::BinaryExpression(Compiler::AST::Expression::Operator::OR,$1,$3);
    }

%%

void yy::parser::error(const location_type& l, const std::string& m) {
     driver.error(l, m);
}

