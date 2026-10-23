# Agent Instructions

## AI Assistance and Attribution

AI assistance is permitted in this repository. Attribution is required.

### When attribution is required

Attribute whenever an AI tool generated or materially shaped something that
lands in the repository: source code, comments, documentation, test cases,
build configuration, or the commit and PR text itself.

Attribution is not required when the assistant never touched what you committed,
such as editor autocomplete of a symbol name, asking a model to explain existing
code, or using one to search the codebase or the literature.

The line to apply: would a reviewer reading this diff want to know an AI wrote
it? When in doubt, attribute.

### How to attribute

- **Commit trailer.** Every commit whose content an AI generated or materially
  shaped carries a `Co-authored-by:` trailer naming the model or tool, in the
  trailer block after a blank line at the end of the commit message.
- **PR description.** State briefly what the AI did and what the human verified.
  A commit trailer is invisible in the GitHub review UI; the prose note is what
  the reviewer sees.

### What attribution does not change

Attribution is a disclosure, not a disclaimer. The human contributor is the
author of record and remains responsible for the change:

- **Correctness.** You must understand the code you submit and be able to
  explain and defend it in review. "The model wrote it" is not an answer to a
  review question.
- **Testing.** AI-generated code is held to the same standard as any other: it
  needs tests, and it must pass the project's checks.
- **Scientific claims.** Equations, coefficients, and numerical results must be
  validated against a trusted reference, such as the IAPWS verification tables
  or the forward equations. Never accept a result because a model produced it
  confidently, and report the measured error, not only that tests passed.
- **Provenance and licensing.** By submitting, you assert the contribution is
  yours to give under this repository's MIT license. Verify that generated code
  is not a verbatim reproduction of incompatibly licensed source, and cite the
  IAPWS release, paper, or table behind any equation or data you add.
