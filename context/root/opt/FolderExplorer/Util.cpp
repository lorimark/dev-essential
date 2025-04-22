

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

#include <dirent.h>
#include <sys/types.h>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>


#include "Util.h"

std::string FolderExplorer::getMimeType( const std::string fileName )
{
  std::map< std::string, std::string > mimeTypes =
  {
    { "3dm",       "x-world/x-3dmf" },
    { "3dmf",      "x-world/x-3dmf"           },
    { "a",         "application/octet-stream" },
    { "aab",       "application/x-authorware-bin" },
    { "aam",       "application/x-authorware-map" },
    { "aas",       "application/x-authorware-seg" },
    { "abc",       "text/vnd.abc" },
    { "acgi",      "text/html" },
    { "afl",       "video/animaflex" },
    { "ai",        "application/postscript" },
//    { "aif",       "audio/aiff" },
    { "aif",       "audio/x-aiff" },
//    { "aifc",      "audio/aiff" },
    { "aifc",      "audio/x-aiff" },
//    { "aiff",      "audio/aiff" },
    { "aiff",      "audio/x-aiff" },
    { "aim",       "application/x-aim" },
    { "aip",       "text/x-audiosoft-intra" },
    { "ani",       "application/x-navi-animation" },
    { "aos",       "application/x-nokia-9000-communicator-add-on-software" },
    { "aps",       "application/mime" },
    { "arc",       "application/octet-stream" },
//    { "arj",       "application/arj" },
    { "arj",       "application/octet-stream" },
    { "art",       "image/x-jg" },
    { "asf",       "video/x-ms-asf" },
    { "asm",       "text/x-asm" },
    { "asp",       "text/asp" },
    { "asx",       "application/x-mplayer2" },
    { "asx",       "video/x-ms-asf" },
    { "asx",       "video/x-ms-asf-plugin" },
    { "au",        "audio/basic" },
    { "au",        "audio/x-au" },
//    { "avi",       "application/x-troff-msvideo" },
    { "avi",       "video/avi" },
//    { "avi",       "video/msvideo" },
//    { "avi",       "video/x-msvideo" },
    { "avs",       "video/avs-video" },
    { "bcpio",     "application/x-bcpio" },
//    { "bin",       "application/mac-binary" },
//    { "bin",       "application/macbinary" },
//    { "bin",       "application/octet-stream" },
    { "bin",       "application/x-binary" },
//    { "bin",       "application/x-macbinary" },
    { "bm",        "image/bmp" },
//    { "bmp",       "image/bmp" },
    { "bmp",       "image/x-windows-bmp" },
    { "boo",       "application/book" },
    { "book",      "application/book" },
    { "boz",       "application/x-bzip2" },
    { "bsh",       "application/x-bsh" },
    { "bz",        "application/x-bzip" },
    { "bz2",       "application/x-bzip2" },
    { "c",         "text/plain" },
    { "c",         "text/x-c" },
    { "c++",       "text/plain" },
    { "cat",       "application/vnd.ms-pki.seccat" },
    { "cc",        "text/plain" },
//    { "cc",        "text/x-c" },
    { "ccad",      "application/clariscad" },
    { "cco",       "application/x-cocoa" },
    { "cdf",       "application/cdf" },
//    { "cdf",       "application/x-cdf" },
//    { "cdf",       "application/x-netcdf" },
    { "cer",       "application/pkix-cert" },
//    { "cer",       "application/x-x509-ca-cert" },
    { "cha",       "application/x-chat" },
    { "chat",      "application/x-chat" },
    { "class",     "application/java" },
//    { "class",     "application/java-byte-code" },
//    { "class",     "application/x-java-class" },
    { "com",       "application/octet-stream" },
//    { "com",       "text/plain" },
    { "conf",      "text/plain" },
    { "cpio",      "application/x-cpio" },
    { "cpp",       "text/x-c" },
//    { "cpt",       "application/mac-compactpro" },
//    { "cpt",       "application/x-compactpro" },
    { "cpt",       "application/x-cpt" },
//    { "crl",       "application/pkcs-crl" },
//    { "crl",       "application/pkix-crl" },
//    { "crt",       "application/pkix-cert" },
//    { "crt",       "application/x-x509-ca-cert" },
    { "crt",       "application/x-x509-user-cert" },
    { "csh",       "application/x-csh" },
//    { "csh",       "text/x-script.csh" },
//    { "css",       "application/x-pointplus" },
    { "css",       "text/css" },
    { "cxx",       "text/plain" },
    { "dcr",       "application/x-director" },
    { "deepv",     "application/x-deepv" },
    { "def",       "text/plain" },
    { "der",       "application/x-x509-ca-cert" },
    { "dif",       "video/x-dv" },
    { "dir",       "application/x-director" },
//    { "dl",        "video/dl" },
    { "dl",        "video/x-dl" },
    { "doc",       "application/msword" },
    { "dot",       "application/msword" },
    { "dp",        "application/commonground" },
    { "drw",       "application/drafting" },
    { "dump",      "application/octet-stream" },
    { "dv",        "video/x-dv" },
    { "dvi",       "application/x-dvi" },
//    { "dwf",       "drawing/x-dwf (old)" },
    { "dwf",       "model/vnd.dwf" },
    { "dwg",       "application/acad" },
//    { "dwg",       "image/vnd.dwg" },
//    { "dwg",       "image/x-dwg" },
    { "dxf",       "application/dxf" },
//    { "dxf",       "image/vnd.dwg" },
//    { "dxf",       "image/x-dwg" },
    { "dxr",       "application/x-director" },
    { "el",        "text/x-script.elisp" },
//    { "elc",       "application/x-bytecode.elisp (compiled elisp)" },
    { "elc",       "application/x-elc" },
    { "env",       "application/x-envoy" },
    { "eps",       "application/postscript" },
    { "es",        "application/x-esrehber" },
    { "etx",       "text/x-setext" },
    { "evy",       "application/envoy" },
    { "evy",       "application/x-envoy" },
    { "exe",       "application/octet-stream" },
    { "f",         "text/plain" },
//    { "f",         "text/x-fortran" },
    { "f77",       "text/x-fortran" },
    { "f90",       "text/plain" },
//    { "f90",       "text/x-fortran" },
    { "fdf",       "application/vnd.fdf" },
//    { "fif",       "application/fractals" },
    { "fif",       "image/fif" },
    { "fli",       "video/fli" },
//    { "fli",       "video/x-fli" },
    { "flo",       "image/florian" },
    { "flx",       "text/vnd.fmi.flexstor" },
    { "fmf",       "video/x-atomic3d-feature" },
    { "for",       "text/plain" },
//    { "for",       "text/x-fortran" },
    { "fpx",       "image/vnd.fpx" },
//    { "fpx",       "image/vnd.net-fpx" },
    { "frl",       "application/freeloader" },
    { "funk",      "audio/make" },
    { "g",         "text/plain" },
    { "g3",        "image/g3fax" },
    { "gif",       "image/gif" },
    { "gl",        "video/gl" },
//    { "gl",        "video/x-gl" },
    { "gsd",       "audio/x-gsm" },
    { "gsm",       "audio/x-gsm" },
    { "gsp",       "application/x-gsp" },
    { "gss",       "application/x-gss" },
    { "gtar",      "application/x-gtar" },
//    { "gz",        "application/x-compressed" },
    { "gz",        "application/x-gzip" },
//    { "gzip",      "application/x-gzip" },
    { "gzip",      "multipart/x-gzip" },
//    { "h",         "text/plain" },
    { "h",         "text/x-h" },
    { "hdf",       "application/x-hdf" },
    { "help",      "application/x-helpfile" },
    { "hgl",       "application/vnd.hp-hpgl" },
//    { "hh",        "text/plain" },
    { "hh",        "text/x-h" },
    { "hlb",       "text/x-script" },
    { "hlp",       "application/hlp" },
//    { "hlp",       "application/x-helpfile" },
//    { "hlp",       "application/x-winhelp" },
    { "hpg",       "application/vnd.hp-hpgl" },
    { "hpgl",      "application/vnd.hp-hpgl" },
    { "hqx",       "application/binhex" },
//    { "hqx",       "application/binhex4" },
//    { "hqx",       "application/mac-binhex" },
//    { "hqx",       "application/mac-binhex40" },
//    { "hqx",       "application/x-binhex40" },
//    { "hqx",       "application/x-mac-binhex40" },
    { "hta",       "application/hta" },
    { "htc",       "text/x-component" },
    { "htm",       "text/html" },
    { "html",      "text/html" },
    { "htmls",     "text/html" },
    { "htt",       "text/webviewhtml" },
    { "htx",       "text/html" },
    { "ice",       "x-conference/x-cooltalk" },
    { "ico",       "image/x-icon" },
    { "idc",       "text/plain" },
    { "ief",       "image/ief" },
    { "iefs",      "image/ief" },
    { "iges",      "application/iges" },
//    { "iges",      "model/iges" },
    { "igs",       "application/iges" },
//    { "igs",       "model/iges" },
    { "ima",       "application/x-ima" },
    { "imap",      "application/x-httpd-imap" },
    { "inf",       "application/inf" },
    { "ins",       "application/x-internett-signup" },
    { "ip",        "application/x-ip2" },
    { "isu",       "video/x-isvideo" },
    { "it",        "audio/it" },
    { "iv",        "application/x-inventor" },
    { "ivr",       "i-world/i-vrml" },
    { "ivy",       "application/x-livescreen" },
    { "jam",       "audio/x-jam" },
    { "jav",       "text/plain" },
//    { "jav",       "text/x-java-source" },
    { "java",      "text/plain" },
//    { "java",      "text/x-java-source" },
    { "jcm",       "application/x-java-commerce" },
    { "jfif",      "image/jpeg" },
//    { "jfif",      "image/pjpeg" },
    { "jfif-tbnl", "image/jpeg" },
    { "jpe",       "image/jpeg" },
//    { "jpe",       "image/pjpeg" },
    { "jpeg",      "image/jpeg" },
//    { "jpeg",      "image/pjpeg" },
    { "jpg",       "image/jpeg" },
//    { "jpg",       "image/pjpeg" },
    { "jps",       "image/x-jps" },
//    { "js",        "application/x-javascript" },
//    { "js",        "application/javascript" },
//    { "js",        "application/ecmascript" },
    { "js",        "text/javascript" },
//    { "js",        "text/ecmascript" },
    { "jut",       "image/jutvision" },
    { "kar",       "audio/midi" },
//    { "kar",       "music/x-karaoke" },
    { "ksh",       "application/x-ksh" },
//    { "ksh",       "text/x-script.ksh" },
    { "la",        "audio/nspaudio" },
//    { "la",        "audio/x-nspaudio" },
    { "lam",       "audio/x-liveaudio" },
    { "latex",     "application/x-latex" },
    { "lha",       "application/lha" },
  //  { "lha",       "application/octet-stream" },
    { "lha",       "application/x-lha" },
    { "lhx",       "application/octet-stream" },
    { "list",      "text/plain" },
    { "lma",       "audio/nspaudio" },
//    { "lma",       "audio/x-nspaudio" },
    { "log",       "text/plain" },
    { "lsp",       "application/x-lisp" },
//    { "lsp",       "text/x-script.lisp" },
    { "lst",       "text/plain" },
    { "lsx",       "text/x-la-asf" },
    { "ltx",       "application/x-latex" },
//    { "lzh",       "application/octet-stream" },
    { "lzh",       "application/x-lzh" },
    { "lzx",       "application/lzx" },
//    { "lzx",       "application/octet-stream" },
//    { "lzx",       "application/x-lzx" },
    { "m",         "text/plain" },
//    { "m",         "text/x-m" },
    { "m1v",       "video/mpeg" },
    { "m2a",       "audio/mpeg" },
    { "m2v",       "video/mpeg" },
    { "m3u",       "audio/x-mpequrl" },
    { "man",       "application/x-troff-man" },
    { "map",       "application/x-navimap" },
    { "mar",       "text/plain" },
    { "mbd",       "application/mbedlet" },
    { "mc",        "application/x-magic-cap-package-1.0" },
    { "mcd",       "application/mcad" },
//    { "mcd",       "application/x-mathcad" },
//    { "mcf",       "image/vasa" },
    { "mcf",       "text/mcf" },
    { "mcp",       "application/netmc" },
    { "me",        "application/x-troff-me" },
    { "mht",       "message/rfc822" },
    { "mhtml",     "message/rfc822" },
//    { "mid",       "application/x-midi" },
    { "mid",       "audio/midi" },
//    { "mid",       "audio/x-mid" },
//    { "mid",       "audio/x-midi" },
//    { "mid",       "music/crescendo" },
//    { "mid",       "x-music/x-midi" },
//    { "midi",      "application/x-midi" },
    { "midi",      "audio/midi" },
//    { "midi",      "audio/x-mid" },
//    { "midi",      "audio/x-midi" },
//    { "midi",      "music/crescendo" },
//    { "midi",      "x-music/x-midi" },
    { "mif",       "application/x-frame" },
//    { "mif",       "application/x-mif" },
//    { "mime",      "message/rfc822" },
    { "mime",      "www/mime" },
    { "mjf",       "audio/x-vnd.audioexplosion.mjuicemediafile" },
    { "mjpg",      "video/x-motion-jpeg" },
    { "mm",        "application/base64" },
//    { "mm",        "application/x-meme" },
    { "mme",       "application/base64" },
    { "mod",       "audio/mod" },
//    { "mod",       "audio/x-mod" },
    { "moov",      "video/quicktime" },
    { "mov",       "video/quicktime" },
    { "movie",     "video/x-sgi-movie" },
    { "mp2",       "audio/mpeg" },
//    { "mp2",       "audio/x-mpeg" },
//    { "mp2",       "video/mpeg" },
//    { "mp2",       "video/x-mpeg" },
//    { "mp2",       "video/x-mpeq2a" },
    { "mp3",       "audio/mpeg3" },
//    { "mp3",       "audio/x-mpeg-3" },
//    { "mp3",       "video/mpeg" },
//    { "mp3",       "video/x-mpeg" },
    { "mpa",       "audio/mpeg" },
//    { "mpa",       "video/mpeg" },
    { "mpc",       "application/x-project" },
    { "mpe",       "video/mpeg" },
    { "mpeg",      "video/mpeg" },
//    { "mpg",       "audio/mpeg" },
    { "mpg",       "video/mpeg" },
    { "mpga",      "audio/mpeg" },
    { "mpp",       "application/vnd.ms-project" },
    { "mpt",       "application/x-project" },
    { "mpv",       "application/x-project" },
    { "mpx",       "application/x-project" },
    { "mrc",       "application/marc" },
    { "ms",        "application/x-troff-ms" },
    { "mv",        "video/x-sgi-movie" },
    { "my",        "audio/make" },
    { "mzz",       "application/x-vnd.audioexplosion.mzz" },
    { "nap",       "image/naplps" },
    { "naplps",    "image/naplps" },
    { "nc",        "application/x-netcdf" },
    { "ncm",       "application/vnd.nokia.configuration-message" },
    { "nif",       "image/x-niff" },
    { "niff",      "image/x-niff" },
    { "nix",       "application/x-mix-transfer" },
    { "nsc",       "application/x-conference" },
    { "nvd",       "application/x-navidoc" },
    { "o",         "application/octet-stream" },
    { "oda",       "application/oda" },
    { "omc",       "application/x-omc" },
    { "omcd",      "application/x-omcdatamaker" },
    { "omcr",      "application/x-omcregerator" },
    { "p",         "text/x-pascal" },
    { "p10",       "application/pkcs10" },
//    { "p10",       "application/x-pkcs10" },
    { "p12",       "application/pkcs-12" },
//    { "p12",       "application/x-pkcs12" },
    { "p7a",       "application/x-pkcs7-signature" },
    { "p7c",       "application/pkcs7-mime" },
//    { "p7c",       "application/x-pkcs7-mime" },
    { "p7m",       "application/pkcs7-mime" },
//    { "p7m",       "application/x-pkcs7-mime" },
    { "p7r",       "application/x-pkcs7-certreqresp" },
    { "p7s",       "application/pkcs7-signature" },
    { "part",      "application/pro_eng" },
    { "pas",       "text/pascal" },
    { "pbm",       "image/x-portable-bitmap" },
//    { "pcl",       "application/vnd.hp-pcl" },
    { "pcl",       "application/x-pcl" },
    { "pct",       "image/x-pict" },
    { "pcx",       "image/x-pcx" },
    { "pdb",       "chemical/x-pdb" },
    { "pdf",       "application/pdf" },
    { "pfunk",     "audio/make" },
//    { "pfunk",     "audio/make.my.funk" },
    { "pgm",       "image/x-portable-graymap" },
//    { "pgm",       "image/x-portable-greymap" },
    { "pic",       "image/pict" },
    { "pict",      "image/pict" },
    { "pkg",       "application/x-newton-compatible-pkg" },
    { "pko",       "application/vnd.ms-pki.pko" },
    { "pl",        "text/plain" },
//    { "pl",        "text/x-script.perl" },
    { "plx",       "application/x-pixclscript" },
    { "pm",        "image/x-xpixmap" },
//    { "pm",        "text/x-script.perl-module" },
    { "pm4",       "application/x-pagemaker" },
    { "pm5",       "application/x-pagemaker" },
    { "png",       "image/png" },
//    { "pnm",       "application/x-portable-anymap" },
    { "pnm",       "image/x-portable-anymap" },
    { "pot",       "application/mspowerpoint" },
//    { "pot",       "application/vnd.ms-powerpoint" },
    { "pov",       "model/x-pov" },
    { "ppa",       "application/vnd.ms-powerpoint" },
    { "ppm",       "image/x-portable-pixmap" },
    { "pps",       "application/mspowerpoint" },
//    { "pps",       "application/vnd.ms-powerpoint" },
//    { "ppt",       "application/mspowerpoint" },
    { "ppt",       "application/powerpoint" },
//    { "ppt",       "application/vnd.ms-powerpoint" },
//    { "ppt",       "application/x-mspowerpoint" },
    { "ppz",       "application/mspowerpoint" },
    { "pre",       "application/x-freelance" },
    { "prt",       "application/pro_eng" },
    { "ps",        "application/postscript" },
    { "psd",       "application/octet-stream" },
    { "pvu",       "paleovu/x-pv" },
    { "pwz",       "application/vnd.ms-powerpoint" },
    { "py",        "text/x-script.phyton" },
    { "pyc",       "application/x-bytecode.python" },
    { "qcp",       "audio/vnd.qcelp" },
    { "qd3",       "x-world/x-3dmf" },
    { "qd3d",      "x-world/x-3dmf" },
    { "qif",       "image/x-quicktime" },
    { "qt",        "video/quicktime" },
    { "qtc",       "video/x-qtc" },
    { "qti",       "image/x-quicktime" },
    { "qtif",      "image/x-quicktime" },
//    { "ra",        "audio/x-pn-realaudio" },
//    { "ra",        "audio/x-pn-realaudio-plugin" },
    { "ra",        "audio/x-realaudio" },
    { "ram",       "audio/x-pn-realaudio" },
//    { "ras",       "application/x-cmu-raster" },
//    { "ras",       "image/cmu-raster" },
    { "ras",       "image/x-cmu-raster" },
    { "rast",      "image/cmu-raster" },
    { "rexx",      "text/x-script.rexx" },
    { "rf",        "image/vnd.rn-realflash" },
    { "rgb",       "image/x-rgb" },
//    { "rm",        "application/vnd.rn-realmedia" },
    { "rm",        "audio/x-pn-realaudio" },
    { "rmi",       "audio/mid" },
    { "rmm",       "audio/x-pn-realaudio" },
    { "rmp",       "audio/x-pn-realaudio" },
//    { "rmp",       "audio/x-pn-realaudio-plugin" },
    { "rng",       "application/ringing-tones" },
//    { "rng",       "application/vnd.nokia.ringing-tone" },
    { "rnx",       "application/vnd.rn-realplayer" },
    { "roff",      "application/x-troff" },
    { "rp",        "image/vnd.rn-realpix" },
    { "rpm",       "audio/x-pn-realaudio-plugin" },
    { "rt",        "text/richtext" },
//    { "rt",        "text/vnd.rn-realtext" },
//    { "rtf",       "application/rtf" },
//    { "rtf",       "application/x-rtf" },
    { "rtf",       "text/richtext" },
//    { "rtx",       "application/rtf" },
    { "rtx",       "text/richtext" },
    { "rv",        "video/vnd.rn-realvideo" },
    { "s",         "text/x-asm" },
    { "s3m",       "audio/s3m" },
    { "saveme",    "application/octet-stream" },
    { "sbk",       "application/x-tbook" },
//    { "scm",       "application/x-lotusscreencam" },
//    { "scm",       "text/x-script.guile" },
//    { "scm",       "text/x-script.scheme" },
    { "scm",       "video/x-scm" },
    { "sdml",      "text/plain" },
    { "sdp",       "application/sdp" },
//    { "sdp",       "application/x-sdp" },
    { "sdr",       "application/sounder" },
    { "sea",       "application/sea" },
//    { "sea",       "application/x-sea" },
    { "set",       "application/set" },
    { "sgm",       "text/sgml" },
//    { "sgm",       "text/x-sgml" },
    { "sgml",      "text/sgml" },
//    { "sgml",      "text/x-sgml" },
    { "sh",        "application/x-bsh" },
//    { "sh",        "application/x-sh" },
//    { "sh",        "application/x-shar" },
//    { "sh",        "text/x-script.sh" },
    { "shar",      "application/x-bsh" },
//    { "shar",      "application/x-shar" },
    { "shtml",     "text/html" },
//    { "shtml",     "text/x-server-parsed-html" },
    { "sid",       "audio/x-psid" },
    { "sit",       "application/x-sit" },
//    { "sit",       "application/x-stuffit" },
    { "skd",       "application/x-koan" },
    { "skm",       "application/x-koan" },
    { "skp",       "application/x-koan" },
    { "skt",       "application/x-koan" },
    { "sl",        "application/x-seelogo" },
    { "smi",       "application/smil" },
    { "smil",      "application/smil" },
    { "snd",       "audio/basic" },
//    { "snd",       "audio/x-adpcm" },
    { "sol",       "application/solids" },
//    { "spc",       "application/x-pkcs7-certificates" },
    { "spc",       "text/x-speech" },
    { "spl",       "application/futuresplash" },
    { "spr",       "application/x-sprite" },
    { "sprite",    "application/x-sprite" },
    { "src",       "application/x-wais-source" },
    { "ssi",       "text/x-server-parsed-html" },
    { "ssm",       "application/streamingmedia" },
    { "sst",       "application/vnd.ms-pki.certstore" },
    { "step",      "application/step" },
    { "stl",       "application/sla" },
//    { "stl",       "application/vnd.ms-pki.stl" },
//    { "stl",       "application/x-navistyle" },
    { "stp",       "application/step" },
    { "sv4cpio",   "application/x-sv4cpio" },
    { "sv4crc",    "application/x-sv4crc" },
    { "svf",       "image/vnd.dwg" },
//    { "svf",       "image/x-dwg" },
    { "svr",       "application/x-world" },
//    { "svr",       "x-world/x-svr" },
    { "swf",       "application/x-shockwave-flash" },
    { "t",         "application/x-troff" },
    { "talk",      "text/x-speech" },
    { "tar",       "application/x-tar" },
    { "tbk",       "application/toolbook" },
//    { "tbk",       "application/x-tbook" },
    { "tcl",       "application/x-tcl" },
//    { "tcl",       "text/x-script.tcl" },
    { "tcsh",      "text/x-script.tcsh" },
    { "tex",       "application/x-tex" },
    { "texi",      "application/x-texinfo" },
    { "texinfo",   "application/x-texinfo" },
//    { "text",      "application/plain" },
    { "text",      "text/plain" },
    { "tgz",       "application/gnutar" },
//    { "tgz",       "application/x-compressed" },
    { "tif",       "image/tiff" },
//    { "tif",       "image/x-tiff" },
    { "tiff",      "image/tiff" },
//    { "tiff",      "image/x-tiff" },
    { "tr",        "application/x-troff" },
    { "tsi",       "audio/tsp-audio" },
//    { "tsp",       "application/dsptype" },
    { "tsp",       "audio/tsplayer" },
    { "tsv",       "text/tab-separated-values" },
    { "turbot",    "image/florian" },
    { "txt",       "text/plain" },
    { "uil",       "text/x-uil" },
    { "uni",       "text/uri-list" },
    { "unis",      "text/uri-list" },
    { "unv",       "application/i-deas" },
    { "uri",       "text/uri-list" },
    { "uris",      "text/uri-list" },
    { "ustar",     "application/x-ustar" },
//    { "ustar",     "multipart/x-ustar" },
//    { "uu",        "application/octet-stream" },
    { "uu",        "text/x-uuencode" },
    { "uue",       "text/x-uuencode" },
    { "vcd",       "application/x-cdlink" },
    { "vcs",       "text/x-vcalendar" },
    { "vda",       "application/vda" },
    { "vdo",       "video/vdo" },
    { "vew",       "application/groupwise" },
    { "viv",       "video/vivo" },
//    { "viv",       "video/vnd.vivo" },
    { "vivo",      "video/vivo" },
//    { "vivo",      "video/vnd.vivo" },
    { "vmd",       "application/vocaltec-media-desc" },
    { "vmf",       "application/vocaltec-media-file" },
    { "voc",       "audio/voc" },
//    { "voc",       "audio/x-voc" },
    { "vos",       "video/vosaic" },
    { "vox",       "audio/voxware" },
    { "vqe",       "audio/x-twinvq-plugin" },
    { "vqf",       "audio/x-twinvq" },
    { "vql",       "audio/x-twinvq-plugin" },
    { "vrml",      "application/x-vrml" },
//    { "vrml",      "model/vrml" },
//    { "vrml",      "x-world/x-vrml" },
    { "vrt",       "x-world/x-vrt" },
    { "vsd",       "application/x-visio" },
    { "vst",       "application/x-visio" },
    { "vsw",       "application/x-visio" },
    { "w60",       "application/wordperfect6.0" },
    { "w61",       "application/wordperfect6.1" },
    { "w6w",       "application/msword" },
    { "wav",       "audio/wav" },
//    { "wav",       "audio/x-wav" },
    { "wb1",       "application/x-qpro" },
    { "wbmp",      "image/vnd.wap.wbmp" },
    { "web",       "application/vnd.xara" },
    { "wiz",       "application/msword" },
    { "wk1",       "application/x-123" },
    { "wmf",       "windows/metafile" },
    { "wml",       "text/vnd.wap.wml" },
    { "wmlc",      "application/vnd.wap.wmlc" },
    { "wmls",      "text/vnd.wap.wmlscript" },
    { "wmlsc",     "application/vnd.wap.wmlscriptc" },
    { "word",      "application/msword" },
    { "wp",        "application/wordperfect" },
    { "wp5",       "application/wordperfect" },
//    { "wp5",       "application/wordperfect6.0" },
    { "wp6",       "application/wordperfect" },
    { "wpd",       "application/wordperfect" },
//    { "wpd",       "application/x-wpwin" },
    { "wq1",       "application/x-lotus" },
    { "wri",       "application/mswrite" },
//    { "wri",       "application/x-wri" },
    { "wrl",       "application/x-world" },
    { "wrl",       "model/vrml" },
    { "wrl",       "x-world/x-vrml" },
    { "wrz",       "model/vrml" },
    { "wrz",       "x-world/x-vrml" },
    { "wsc",       "text/scriplet" },
    { "wsrc",      "application/x-wais-source" },
    { "wtk",       "application/x-wintalk" },
//    { "xbm",       "image/x-xbitmap" },
//    { "xbm",       "image/x-xbm" },
    { "xbm",       "image/xbm" },
    { "xdr",       "video/x-amt-demorun" },
    { "xgz",       "xgl/drawing" },
    { "xif",       "image/vnd.xiff" },
    { "xl",        "application/excel" },
    { "xla",       "application/excel" },
//    { "xla",       "application/x-excel" },
//    { "xla",       "application/x-msexcel" },
    { "xlb",       "application/excel" },
//    { "xlb",       "application/vnd.ms-excel" },
//    { "xlb",       "application/x-excel" },
    { "xlc",       "application/excel" },
//    { "xlc",       "application/vnd.ms-excel" },
//    { "xlc",       "application/x-excel" },
    { "xld",       "application/excel" },
//    { "xld",       "application/x-excel" },
    { "xlk",       "application/excel" },
//    { "xlk",       "application/x-excel" },
    { "xll",       "application/excel" },
//    { "xll",       "application/vnd.ms-excel" },
//    { "xll",       "application/x-excel" },
    { "xlm",       "application/excel" },
//    { "xlm",       "application/vnd.ms-excel" },
//    { "xlm",       "application/x-excel" },
    { "xls",       "application/excel" },
//    { "xls",       "application/vnd.ms-excel" },
//    { "xls",       "application/x-excel" },
//    { "xls",       "application/x-msexcel" },
    { "xlt",       "application/excel" },
//    { "xlt",       "application/x-excel" },
    { "xlv",       "application/excel" },
//    { "xlv",       "application/x-excel" },
    { "xlw",       "application/excel" },
//    { "xlw",       "application/vnd.ms-excel" },
//    { "xlw",       "application/x-excel" },
//    { "xlw",       "application/x-msexcel" },
    { "xm",        "audio/xm" },
    { "xml",       "application/xml" },
//    { "xml",       "text/xml" },
    { "xmz",       "xgl/movie" },
    { "xpix",      "application/x-vnd.ls-xpix" },
//    { "xpm",       "image/x-xpixmap" },
    { "xpm",       "image/xpm" },
    { "x-png",     "image/png" },
    { "xsr",       "video/x-amt-showrun" },
    { "xwd",       "image/x-xwd" },
//    { "xwd",       "image/x-xwindowdump" },
    { "xyz",       "chemical/x-pdb" },
    { "z",         "application/x-compress" },
//    { "z",         "application/x-compressed" },
//    { "zip",       "application/x-compressed" },
//    { "zip",       "application/x-zip-compressed" },
    { "zip",       "application/zip" },
//    { "zip",       "multipart/x-zip" },
    { "zoo",       "application/octet-stream" },
    { "zsh",       "text/x-script.zsh" }
  };

  std::string retVal;
  auto pos = fileName.find_last_of(".");

  if( pos != std::string::npos )
  {
    retVal = mimeTypes[ fileName.substr( pos + 1 ) ];
  }

  return retVal;

} // endstd::string getMimeType( const std::string fileName )


std::string FolderExplorer::fixPath( const std::string path )
{
  std::string retVal = path;

  if( retVal.back() != '/' )
    retVal += "/";

  return retVal;
}

void FolderExplorer::split( const std::string & str, char delim, std::vector< std::string > & elems )
{
  std::stringstream ss;
  ss.str(str);
  std::string item;
  while( std::getline( ss, item, delim) )
  {
    elems.push_back(item);
  }
}

std::vector<std::string> FolderExplorer::split( const std::string & str, char delim )
{
  std::vector<std::string> retVal;

  split( str, delim, retVal );

  return retVal;
}

/*!
** \brief move up one path position
**
** \todo this routine doesn't handle ../rootfolder/somefolder having
**  the .. at the beginning of the path.
*/
std::string FolderExplorer::upPath( const std::string path )
{
  std::string retVal;

  auto elems = split( path, '/' );

  for( auto i=elems.begin(); i != elems.end()-2; i++ )
  {
    retVal += *i + "/";
  }

  return retVal;
}

bool FolderExplorer::contains( const std::string & inString, const std::string & containString )
{
  if( inString.length() >= containString.length() )
  {
    return std::string::npos !=
      inString.find( containString );

  }

  return false;
}

bool FolderExplorer::beginsWith( const std::string & inString, const std::string & beginString )
{
  if( inString.length() >= beginString.length() )
  {
    return 0 ==
      inString.compare
      (
        0,
        beginString.length(),
        beginString
      );

  }

  return false;
}

bool FolderExplorer::endsWith( const std::string & inString, const std::string & endString )
{
  if( inString.length() >= endString.length() )
  {
    return 0 ==
      inString.compare
      (
        inString.length() - endString.length(),
        endString.length(),
        endString
      );

  }

  return false;
}

std::string FolderExplorer::removeBadFileNameChars( const std::string & fileName )
{
  std::string fn = fileName;

  char chars[] = "#<$+%>!`&*'|{?\"=}/:\\@";

  for( unsigned int i=0; i< strlen(chars); i++ )
  {
//BUGBUG    fn.erase( std::remove( fn.begin(), fn.end(), chars[i]), fn.end() );
  }

  return fn;
}

/*
** This function produces a case-insensitive sort of
**  the files and folders in a directory.  The file
**  items are converted to upper-case so that case
**  becomes ignored, and then the function uses the
**  strverscmp function which causes jan-1, jan-2,
**  jan-10 to be sorted in that order, which can
**  make a little more logical sense when looking at
**  folder names.
**
** https://linux.die.net/man/3/scandir
**
*/
int FolderExplorer::ialphasort( const struct dirent **a, const struct dirent **b )
{
  std::string ua = (*a)-> d_name;
  std::transform( ua.begin(), ua.end(), ua.begin(), ::toupper );

  std::string ub = (*b)-> d_name;
  std::transform( ub.begin(), ub.end(), ub.begin(), ::toupper );

  return strverscmp( ua.c_str(), ub.c_str() );
}

std::string FolderExplorer::tooltip( const std::string & path, const std::string & filename )
{
  return filename;
}

std::vector<FolderExplorer::FileInfo> FolderExplorer::getFileInfo( const std::string & folder )
{
  std::vector<FolderExplorer::FileInfo> retVal;

  /*
  ** pull up all the items in this folder
  **
  */
  struct dirent ** namelist;
  int n = scandir( folder.c_str(), &namelist, 0, ialphasort );

  if( n > 0 )
  {
    /*
    ** loop through all the items in the folder
    **
    */
    for( int i=0; i< n; i++ )
    {
      /*
      ** pull the folder name from the items list
      **  and free the original source
      **
      */
      std::string fileName( namelist[i]-> d_name );
      free( namelist[i] );

      /*
      ** single '.' dot items are ignored totally
      */
      if( fileName == "." )
        continue;

      /*
      ** make something that represents the full file path
      **
      */
      std::string filePath( folder + "/" + fileName );

      /*
      ** the 'fileStat' value contains the following flags
      **  and status codes.  grab the filestat based on the 'stat'
      **  function call so that the file can be parsed.
      **
      **  st_atime
      **  st_atime
      **  st_ctime
      **  st_ctime
      **  st_gid
      **  st_gid
      **  st_ino
      **  st_mtime
      **  st_mtime
      **  st_nlink
      **  st_mode
      **  st_mode
      **  st_size
      **  st_uid
      **  st_uid
      **
      */
      struct stat fileStat;
      int result = stat( filePath.c_str(), &fileStat );

      /*
      ** there should always be a result on pulling the
      **  file stat.
      */
      if( result == 0 )
      {
        FileInfo fileInfo( fileName, fileStat );

        retVal.push_back( fileInfo );

      }

    }

    free( namelist );
  }

  return retVal;

} // endstd::vector<FolderExplorer::FileInfo> FolderExplorer::getFileInfo( const std::string folder )



