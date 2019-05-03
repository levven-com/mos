//
// Copyright (c) 2014-2019 Cesanta Software Limited
// All rights reserved
//
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
package frame

import (
	"io"

	"github.com/cesanta/errors"
)

type limitedWriter struct {
	io.Writer
	limit int
}

// New returns a new limited writer.
//
// A limited writer will return error after writing limit bytes.
func NewLimitedWriter(w io.Writer, limit int) io.Writer {
	return &limitedWriter{w, limit}
}

func (w *limitedWriter) Write(b []byte) (int, error) {
	limited := false
	if len(b) > w.limit {
		b = b[:w.limit]
		limited = true
	}
	w.limit -= len(b)

	n, err := w.Writer.Write(b)
	if limited && err == nil {
		return n, io.EOF
	}
	return n, errors.Trace(err)
}