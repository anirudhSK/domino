#ifndef CHIPMUNK_CODE_GENERATOR_H_
#define CHIPMUNK_CODE_GENERATOR_H_

#include "ast_visitor.h"
#include <map>
#include <string>

class ChipmunkCodeGenerator : public AstVisitor {
 public:
  std::string ast_visit_transform(const clang::TranslationUnitDecl * tu_decl) override;
  void print_map(); //cout the content of map

 protected:
  std::string ast_visit_member_expr(const clang::MemberExpr * member_expr) override;
  std::string ast_visit_array_subscript_expr(const clang::ArraySubscriptExpr * array_subscript_expr) override;
  std::string ast_visit_decl_ref_expr(const clang::DeclRefExpr * decl_ref_expr) override;
  
  int count_stateful = 0;
  int count_stateless = 0;

  // TODO: This strange typedef is to address an issue with gcc:
  // https://stackoverflow.com/a/28803798/1152801
  typedef std::map<std::string, std::string> DominoToSketchRenamer;
  DominoToSketchRenamer c_to_sk = DominoToSketchRenamer();
};

#endif // CHIPMUNK_CODE_GENERATOR_H_
