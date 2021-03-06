// farextract.cc

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Copyright 2005-2010 Google, Inc.
// Author: riley@google.com (Michael Riley)
// Modified: jpr@google.com (Jake Ratkiewicz) to use new arc dispatch
//
// \file
// Extracts component FSTs from an finite-state archive.
//

#include <fst/extensions/far/main.h>
#include <fst/extensions/far/farscript.h>

DEFINE_string(filename_prefix, "", "Prefix to append to filenames");
DEFINE_string(filename_suffix, "", "Suffix to append to filenames");
DEFINE_int32(generate_filenames, 0,
             "Generate N digit numeric filenames (def: use keys)");
DEFINE_string(begin_key, "",
              "First key to extract (def: first key in archive)");
DEFINE_string(end_key, "",
              "Last key to extract (def: last key in archive)");


int main(int argc, char **argv) {
  namespace s = fst::script;

  string usage = "Extracts FSTs from a finite-state archive.\n\n Usage:";
  usage += argv[0];
  usage += " in1.far [in2.far...]\n";

  std::set_new_handler(FailedNewHandler);
  SetFlags(usage.c_str(), &argc, &argv, true);

  if (argc < 2) {
    ShowUsage();
    return 1;
  }

  vector<string> ifilenames;
  for (int i = 1; i < argc; ++i)
    ifilenames.push_back(argv[i]);

  const string &arc_type = fst::LoadArcTypeFromFar(ifilenames[0]);

  s::FarExtract(ifilenames, arc_type, FLAGS_generate_filenames,
                FLAGS_begin_key, FLAGS_end_key, FLAGS_filename_prefix,
                FLAGS_filename_suffix);

  return 0;
}
