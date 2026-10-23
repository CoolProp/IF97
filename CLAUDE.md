# Project Instructions for AI Agents

This file provides instructions and context for AI coding agents working on this project.

## Attribution (REQUIRED)

Work you produce here must be attributed. Every commit whose content you
generated or materially shaped carries a `Co-authored-by:` trailer naming the
model, and the PR body states what you did and what the human verified. Full
policy, including what attribution does not change:
[`AGENTS.md`](AGENTS.md#ai-assistance-and-attribution).

```
Co-authored-by: Claude Opus 5 <noreply@anthropic.com>
```

A maintainer's untracked `CLAUDE.local.md` may override the model name and
other personal preferences; follow it where it exists.

## Project Overview

IF97 is a header-only C++ implementation of the IAPWS Industrial Formulation
1997 for the thermodynamic properties of water and steam, plus the IAPWS
supplementary releases and backward equations.

- `IF97.h` is the library. `IF97.cpp` is the verification program (it prints
  results that are checked against the IAPWS tables), and it is the test suite.
- `wrapper/Mathcad/` holds the Mathcad Prime and Mathcad 15 wrappers.
- CoolProp consumes `IF97.h` through a pinned commit in its
  `cmake/dependencies.cmake`. Treat the public functions in the `IF97`
  namespace as API: adding one is a minor version bump, and changing the
  behavior of an existing one needs a note in the README.
- Compiler flags are documented in `README.md` (for example `IAPWS_UNITS` and
  `REGION3_NO_ITERATE`). Keep the README in step with any flag you add or change.
- Do not edit or commit anything in the CoolProp repo from an IF97 session.
  Cross-repo work goes through handoff files that the user relays.

## Build and Test

```bash
# Configure (one-time). With no wrapper option selected, CMake builds the test executable.
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release

# Build and run the verification program
cmake --build build --config Release
./build/IF97            # on Windows with Visual Studio: build/Release/IF97.exe
```

Check the output for changed numbers, not only for crashes. A change that is
not meant to alter results should leave the program output identical, apart
from any text you edited on purpose.

The Mathcad wrappers build with `-DIF97_PRIME_MODULE=ON` or
`-DIF97_MATHCAD15_MODULE=ON` and need the Mathcad SDK. If you cannot build a
wrapper, say so in your report and do not describe the edit as tested.

## Conventions and Patterns

### Line endings

`IF97.h`, `IF97.cpp`, and the wrapper sources use CRLF line endings in the
working tree (some files are mixed). Preserve them. Scripted edits must detect
the existing line ending and write it back unchanged, or the diff will show the
whole file as changed.

### Numerical changes

- Verify accuracy against the forward equations or the IAPWS table values, and
  report the worst-case error you measured, not just that tests passed.
- Region 3 density is iterated by default. Anything near the critical point,
  including the vapor dome (h,s) functions, depends on that. Test with the
  default, and test with `REGION3_NO_ITERATE` defined only to confirm that the
  documented limits still hold.
- Do not assume exact comparisons survive round-off. Saturation edge states are
  the usual place this bites.
- Backward equations are IAPWS equations. Anything else that solves iteratively
  (for example `DomeSolve_HS`) must say so in its comment, including its speed
  relative to the IAPWS equations.

### Versioning

`IF97VERSION` in `IF97.h` follows semantic versioning: a new public function is
a minor bump, a bug fix or behavior change with no new API is a patch bump. The
README text that mentions a version must match.

### Pre-PR review

Before opening a pull request, review the final diff against the branch's
actual base (for a stacked branch that is the parent branch, not always
`master`). Use a review subagent if one is available. For every check, guard,
or tolerance in the diff, ask what input makes it pass when it should fail. A
safeguard that can silently do nothing is a blocking finding. If you judge an
issue to be an acceptable trade-off, report it as a flagged trade-off rather
than dropping it. Any commit added after the review is unreviewed, so re-review it.

## Session Completion

**When ending a work session**, you MUST complete ALL steps below. Work is NOT complete until `git push` succeeds.

1. Run the verification program and report what passed, what failed, and what you did not test.
2. Make sure all changes are committed, with the attribution trailers above.
3. **PUSH TO REMOTE** (this is MANDATORY):
   ```bash
   git pull --rebase
   git push
   git status  # MUST show "up to date with origin"
   ```
4. Clean up scratch files you created in the repo, and prune stale branches.
5. Hand off: state the branch, the commit SHAs, and what the next session needs to decide.

**CRITICAL RULES:**
- Work is NOT complete until `git push` succeeds.
- NEVER stop before pushing; that leaves work stranded locally.
- If push fails, resolve and retry until it succeeds.
