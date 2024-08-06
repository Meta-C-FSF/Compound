#ifndef COMPOUND_CHAR_H
# define COMPOUND_CHAR_H

# include <Compound/common.h>
# include <Compound/status.h>

typedef struct {
  int value;
  size_t width;
} Char;

typedef struct {
  Char *data;
  int len;
  bool alive;
} CharSeq;

Status CharSeq_Create(CharSeq *inst, int len);
Status CharSeq_CopyOf(CharSeq *inst, CharSeq *other);
Status CharSeq_Delete(CharSeq *inst);

virtual(Status CharSeqUtils_FromCharBuff(CharSeq *inst, char const *buff));
virtual(Status CharSeqUtils_FromWideCharBuff(CharSeq *inst, wchar_t const *wbuff));
virtual(Status CharSeqUtils_ToCharBuff(CharSeq *inst, char const *buff));
virtual(Status CharSeqUtils_ToWideCharBuff(CharSeq *inst, wchar_t const *wbuff));
virtual(Status CharSeqUtils_Tokenise(CharSeq *inst, const CharSeq *delim, CharSeq *store));
virtual(int    CharSeqUtils_Compare(CharSeq *a, CharSeq *b));

#endif  /* COMPOUND_CHAR_H */
