%skeleton "lalr1.cc"

%code requires {
    #include "ast.hpp"
    #include "value.hpp"
    
    namespace SED{
        namespace Driver{
            class Driver;
        }
    }
    using Driver = SED::Driver::Driver;
}

%code {
    #include "driver.hpp"
    #include "context.hpp"
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

%type < SED::AST::Assignment* > Def
%type < SED::AST::Node* > Stmt
%type < SED::AST::FunctionDeclaration* > FuncDecl
%type <SED::AST::Variable*> Var
%type < std::vector< SED::AST::VariableDeclaration* > > DeclList
%type < std::vector< SED::AST::Assignment* > > DefList
%type < SED::AST::Value* > UnaryExp MulExp AddExp RelExp EqExp LAndExp LOrExp PrimaryExp Exp Val 
%type < SED::Enumeration::Operator > UNARYOP
%type < SED::Enumeration::ValueType > Type
%type < SED::AST::FunctionDefinition* > FuncDef
%type < SED::AST::Block* > Block
%type < SED::AST::CompilationUnit* > CompUnit
%type < std::vector< SED::AST::Node* > > BlockItemList
%type < std::vector< SED::AST::Node* > > CompUnitContainer
%type < std::vector< SED::AST::VariableDeclaration* > > FuncFParams
%type < std::vector< SED::AST::Value* > > FuncRParams
%token <std::string> IDENT
%token RETURN CONST
%token TYPE_INT TYPE_VOID TYPE_FLOAT TYPE_BOOL TYPE_CHAR
%token<std::int32_t> INT_CONST
%token<float> FLOAT_CONST 
%token<char> CHAR_CONST
%token LPAREN  SEMICOLON COMMA LBRACE RBRACE IF WHILE CONTINUE
%token PLUS MINUS STAR SLASH PERCENT AND OR EQ NE LT GT LE GE NOT TRUE FALSE BREAK
%right ASSIGN

%nonassoc RPAREN
%nonassoc ELSE
%%
%start CompUnit;

CompUnit:
    CompUnitContainer { 
        if (driver.result == nullptr) {
            driver.result = new SED::AST::CompilationUnit();
        }
        driver.result->setNodes($1);
        $$ = driver.result; 
        $$->begin.line = @1.begin.line;
        $$->begin.column = @1.begin.column;
        $$->end.line = @1.end.line;
        $$->end.column = @1.end.column;
    }
    ;

CompUnitContainer: 
       {/* empty */ $$ = std::vector< SED::AST::Node* >();}
    | CompUnitContainer DeclList { $$ = $1; $$.insert($$.end(),$2.begin(),$2.end()); }
    | CompUnitContainer FuncDef { $$ = $1; $$.push_back($2); }
    | CompUnitContainer FuncDecl { $$ = $1; $$.push_back($2); }
    ;


DeclList :
    Type DefList SEMICOLON {
        std::cout << @1 << @2 << @3 << std::endl;
        $$ = std::vector< SED::AST::VariableDeclaration* >();
        for (auto def : $2) {
            auto decl = (new SED::AST::VariableDeclaration())->setType($1)->setVariable(def->getVariable());
            decl->getVariable()->setValueType($1);
            if (def->getValue() != nullptr) {
                decl->setValue(def->getValue());
            }else{
                decl->setValue(SED::AST::Constant::createValue($1));
            }
            $$.push_back(decl);
            decl->begin.line = @1.begin.line;
            decl->begin.column = @1.begin.column;
            decl->end.line = @3.end.line;
            decl->end.column = @3.end.column;
        }
    }
    | CONST DeclList {
        for (auto decl : $2) {
            decl->setCanReassign(false);
        }
        $$ = $2;
    }
    ;
Type:
    TYPE_INT { $$ = SED::Enumeration::ValueType::INT_32; }
    | TYPE_FLOAT { $$ = SED::Enumeration::ValueType::FLOAT_32; }
    | TYPE_VOID { $$ = SED::Enumeration::ValueType::VOID; }
    | TYPE_BOOL { $$ = SED::Enumeration::ValueType::BOOLEAN; }
    | TYPE_CHAR { $$ = SED::Enumeration::ValueType::CHAR; }
    ;

Def:
    Var { $$ = (new SED::AST::Assignment())->setVariable($1); }
    | Var ASSIGN Val { $$ = (new SED::AST::Assignment())->setVariable($1)->setValue($3); }
    ;

Val:
    Exp { $$ = $1; }
  ;

DefList:
    Def { $$ = std::vector< SED::AST::Assignment* >(); $$.push_back($1); }
    | DefList COMMA Def { $1.push_back($3); $$ = $1; }
    ;

FuncDef:
    Type IDENT LPAREN RPAREN Block {
        $$ = (new SED::AST::FunctionDefinition())->setDeclaration((new SED::AST::FunctionDeclaration())->setReturnType($1)->setName($2))->setBlock($5)->setParameters(std::vector< SED::AST::VariableDeclaration* >());
        $$->begin.line = @1.begin.line;
        $$->begin.column = @1.begin.column;
        $$->end.line = @5.end.line;
        $$->end.column = @5.end.column;
    }
    | Type IDENT LPAREN FuncFParams RPAREN Block {
        auto types = std::vector< SED::Enumeration::ValueType >();
        for (auto decl : $4) {
            types.push_back(decl->getType());
        }
        $$ = (new SED::AST::FunctionDefinition())->setDeclaration((new SED::AST::FunctionDeclaration())->setReturnType($1)->setName($2)->setParameters(types))->setBlock($6)->setParameters($4);
        $$->begin.line = @1.begin.line;
        $$->begin.column = @1.begin.column;
        $$->end.line = @6.end.line;
        $$->end.column = @6.end.column;
    }
    ;

FuncFParams:
    Type IDENT { 
        $$ = std::vector< SED::AST::VariableDeclaration* >({(new SED::AST::VariableDeclaration())->setType($1)->setVariable((new SED::AST::Variable())->setName($2))->setValue(SED::AST::Constant::createValue($1))});
        }
    ;
    | Type {
        $$ = std::vector< SED::AST::VariableDeclaration* >({(new SED::AST::VariableDeclaration())->setType($1)->setVariable((new SED::AST::Variable())->setName(""))->setValue(SED::AST::Constant::createValue($1))});
    }
    | FuncFParams COMMA Type {
        $1.push_back((new SED::AST::VariableDeclaration())->setType($3)->setVariable((new SED::AST::Variable())->setName(""))->setValue(SED::AST::Constant::createValue($3)));
        $$ = $1;
    }
    | FuncFParams COMMA Type IDENT { $1.push_back((new SED::AST::VariableDeclaration())->setType($3)->setVariable((new SED::AST::Variable())->setName($4))->setValue(SED::AST::Constant::createValue($3))); $$ = $1; }
    ;

Block:
    LBRACE BlockItemList RBRACE {
        $$ = (new SED::AST::Block())->setNodes($2);
        $$->begin.line = @1.begin.line;
        $$->begin.column = @1.begin.column;
        $$->end.line = @3.end.line;
        $$->end.column = @3.end.column;
    }
    | LBRACE RBRACE {
        $$ = (new SED::AST::Block());
        $$->begin.line = @1.begin.line;
        $$->begin.column = @1.begin.column;
        $$->end.line = @2.end.line;
        $$->end.column = @2.end.column;
    }
    ;

BlockItemList:
     DeclList { 
        $$ = std::vector< SED::AST::Node* >();
        for (auto decl : $1) {
            $$.push_back(decl);
        }
    }
    | Stmt { $$ = std::vector< SED::AST::Node* >(); $$.push_back($1); }
    | BlockItemList DeclList { $$ = $1; $$.insert($$.end(),$2.begin(),$2.end()); }
    | BlockItemList Stmt { $$ = $1; $$.push_back($2); }
    ;

Stmt:
    Var ASSIGN Exp SEMICOLON {
        $$ = (new SED::AST::Assignment())->setVariable($1)->setValue($3);
        $$->begin.line = @1.begin.line;
        $$->begin.column = @1.begin.column;
        $$->end.line = @4.end.line;
        $$->end.column = @4.end.column;
    }
    | RETURN Exp SEMICOLON {
        $$ = (new SED::AST::ReturnStatement())->setValue($2);
        $$->begin.line = @1.begin.line;
        $$->begin.column = @1.begin.column;
        $$->end.line = @3.end.line;
        $$->end.column = @3.end.column;
    }
    | RETURN SEMICOLON {
        $$ = (new SED::AST::ReturnStatement())->setValue(SED::AST::Constant::createValue(SED::Enumeration::ValueType::VOID));
        $$->begin.line = @1.begin.line;
        $$->begin.column = @1.begin.column;
        $$->end.line = @2.end.line;
        $$->end.column = @2.end.column;
    }
    | Block { $$ = $1; }
    | Exp SEMICOLON { 
        $$ = (new SED::AST::ExpressionStatement())->setValue($1);
        $$->begin.line = @1.begin.line;
        $$->begin.column = @1.begin.column;
        $$->end.line = @2.end.line;
        $$->end.column = @2.end.column;
    }
    | SEMICOLON {}
    | WHILE LPAREN Exp RPAREN Stmt {
        SED::AST::Block* body;
        if (auto block = dynamic_cast<SED::AST::Block*>($5)) {
            body = block;
        }else{
            body = (new SED::AST::Block())->setNodes(std::vector< SED::AST::Node* >({$5}));
        }
        $$ = (new SED::AST::WhileStatement())->setCondition($3)->setBody(body);
        $$->begin.line = @1.begin.line;
        $$->begin.column = @1.begin.column;
        $$->end.line = @5.end.line;
        $$->end.column = @5.end.column;
    }
    | IF LPAREN Exp RPAREN Stmt ELSE Stmt { 
        SED::AST::Block* thenBody;
        if (auto block = dynamic_cast<SED::AST::Block*>($5)) {
            thenBody = block;
        }else{
            thenBody = (new SED::AST::Block())->setNodes(std::vector< SED::AST::Node* >({$5}));
        }
        SED::AST::Block* elseBody;
        if (auto block = dynamic_cast<SED::AST::Block*>($7)) {
            elseBody = block;
        }else{
            elseBody = (new SED::AST::Block())->setNodes(std::vector< SED::AST::Node* >({$7}));
        }
        $$ = (new SED::AST::IfStatement())->setCondition($3)->setThenBody(thenBody)->setElseBody(elseBody);
        $$->begin.line = @1.begin.line;
        $$->begin.column = @1.begin.column;
        $$->end.line = @7.end.line;
        $$->end.column = @7.end.column;
    }
    | IF LPAREN Exp RPAREN Stmt {
        SED::AST::Block* thenBody;
        if (auto block = dynamic_cast<SED::AST::Block*>($5)) {
            thenBody = block;
        }else{
            thenBody = (new SED::AST::Block())->setNodes(std::vector< SED::AST::Node* >({$5}));
        }
        $$ = (new SED::AST::IfStatement())->setCondition($3)->setThenBody(thenBody);
        $$->begin.line = @1.begin.line;
        $$->begin.column = @1.begin.column;
        $$->end.line = @5.end.line;
        $$->end.column = @5.end.column;
    }
    | CONTINUE SEMICOLON {
        $$ = (new SED::AST::ContinueStatement());
        $$->begin.line = @1.begin.line;
        $$->begin.column = @1.begin.column;
        $$->end.line = @2.end.line;
        $$->end.column = @2.end.column;
    }
    | BREAK SEMICOLON {
        $$ = (new SED::AST::BreakStatement());
        $$->begin.line = @1.begin.line;
        $$->begin.column = @1.begin.column;
        $$->end.line = @2.end.line;
        $$->end.column = @2.end.column;
    }
    ;

FuncDecl:
    Type IDENT LPAREN RPAREN SEMICOLON {
        $$ = (new SED::AST::FunctionDeclaration())->setReturnType($1)->setName($2);
    }
    | Type IDENT LPAREN FuncFParams RPAREN SEMICOLON {
        auto types = std::vector< SED::Enumeration::ValueType >();
        for (auto decl : $4) {
            types.push_back(decl->getType());
        }
        $$ = (new SED::AST::FunctionDeclaration())->setReturnType($1)->setName($2)->setParameters(types);
    }

Var
    : IDENT { $$ = (new SED::AST::Variable())->setName($1); }
    ;

Exp:
    LOrExp { $$ = $1; }
    ;


PrimaryExp:
    Var { $$ = $1; }
    | LPAREN Exp RPAREN { $$ = $2; }
    | INT_CONST { $$ = (new SED::AST::Int32())->setValue($1); }
    | FLOAT_CONST { $$ = (new SED::AST::Float32())->setValue($1); }
    | CHAR_CONST { $$ = (new SED::AST::Char())->setValue($1); }
    | TRUE { $$ = (new SED::AST::Boolean())->setValue(true); }
    | FALSE { $$ = (new SED::AST::Boolean())->setValue(false); }
    | IDENT LPAREN RPAREN { 
        $$ = (new SED::AST::FunctionCall())->setName($1);
    }
    | IDENT LPAREN FuncRParams RPAREN {
        $$ = (new SED::AST::FunctionCall())->setName($1)->setArguments($3);
    }
    ;

FuncRParams:
    Exp { $$ = std::vector< SED::AST::Value* >({$1}); }
    | FuncRParams COMMA Exp { $1.push_back($3); $$ = $1; }
    ;

UNARYOP:
    MINUS { $$ = SED::Enumeration::Operator::NEG; }
    | NOT { $$ = SED::Enumeration::Operator::NOT; }
    | PLUS { $$ = SED::Enumeration::Operator::POS; }
    ;

UnaryExp:
    PrimaryExp { $$ = $1; }
    | UNARYOP UnaryExp {
        $$ = (new SED::AST::Unary())->setOp($1)->setExpr($2);
    } 
    | LPAREN TYPE_INT RPAREN UnaryExp {
        try{
            $$ = $4->asInt32();
        }catch(std::runtime_error& e){
            std::cerr << e.what() << std::endl;
            $$ = $4;
            break;
        }
    }
    | LPAREN TYPE_FLOAT RPAREN UnaryExp { 
        try{
            $$ = $4->asFloat32();
        }catch(std::runtime_error& e){
            std::cerr << e.what() << std::endl;
            $$ = $4;
            break;
        }
    }
    | LPAREN TYPE_BOOL RPAREN UnaryExp { 
        try{
            $$ = $4->asBoolean();
        }catch(std::runtime_error& e){
            std::cerr << e.what() << std::endl;
            $$ = $4;
            break;
        }
    }
    | LPAREN TYPE_CHAR RPAREN UnaryExp { 
        try{
            $$ = $4->asChar();
        }catch(std::runtime_error& e){
            std::cerr << e.what() << std::endl;
            $$ = $4;
            break;
        }
    }
    ;

MulExp:
    UnaryExp { $$ = $1; }
    | MulExp STAR UnaryExp { 
        $$ = (new SED::AST::Binary())->setOp(SED::Enumeration::Operator::MUL)->setLeft($1)->setRight($3);
    }
    | MulExp SLASH UnaryExp { 
        $$ = (new SED::AST::Binary())->setOp(SED::Enumeration::Operator::DIV)->setLeft($1)->setRight($3);
    }
    | MulExp PERCENT UnaryExp { 
        $$ = (new SED::AST::Binary())->setOp(SED::Enumeration::Operator::MOD)->setLeft($1)->setRight($3);
    }
    ;

AddExp:
    MulExp { $$ = $1; }
    | AddExp PLUS MulExp { 
        $$ = (new SED::AST::Binary())->setOp(SED::Enumeration::Operator::ADD)->setLeft($1)->setRight($3);
    }
    | AddExp MINUS MulExp { 
        $$ = (new SED::AST::Binary())->setOp(SED::Enumeration::Operator::SUB)->setLeft($1)->setRight($3);
    }
    ;

RelExp:
    AddExp { $$ = $1; } 
    | RelExp LT AddExp { 
        $$ = (new SED::AST::Binary())->setOp(SED::Enumeration::Operator::LT)->setLeft($1)->setRight($3);
    }
    | RelExp GT AddExp { 
        $$ = (new SED::AST::Binary())->setOp(SED::Enumeration::Operator::GT)->setLeft($1)->setRight($3);
    }
    | RelExp LE AddExp { 
        $$ = ( new SED::AST::Binary())->setOp(SED::Enumeration::Operator::LE)->setLeft($1)->setRight($3);
    }
    | RelExp GE AddExp { 
        $$ = (new SED::AST::Binary())->setOp(SED::Enumeration::Operator::GE)->setLeft($1)->setRight($3);
    }
    ;

EqExp:
    RelExp { $$ = $1; }
    | EqExp EQ RelExp { 
        $$ = (new SED::AST::Binary())->setOp(SED::Enumeration::Operator::EQ)->setLeft($1)->setRight($3);
    }
    | EqExp NE RelExp { 
        $$ = (new SED::AST::Binary())->setOp(SED::Enumeration::Operator::NE)->setLeft($1)->setRight($3);
    }
    ;

LAndExp:
    EqExp { $$ = $1; }
    | LAndExp AND EqExp { 
        $$ = (new SED::AST::Binary())->setOp(SED::Enumeration::Operator::AND)->setLeft($1)->setRight($3);
    }

LOrExp:
    LAndExp { $$ = $1; }
    | LOrExp OR LAndExp { 
        $$ = (new SED::AST::Binary())->setOp(SED::Enumeration::Operator::OR)->setLeft($1)->setRight($3);
    }

%%

void yy::parser::error(const location_type& l, const std::string& m) {
    driver.error(l, m);
}

