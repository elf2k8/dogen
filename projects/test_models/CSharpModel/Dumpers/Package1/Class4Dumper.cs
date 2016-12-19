// -*- mode: csharp; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
//
// Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
// MA 02110-1301, USA.
//
namespace Dogen.TestModels.CSharpModel.Package1
{
    /// <summary>
    /// Generates sequences of Class4.
    /// </summary>
    public static class Class4Dumper
    {
        static void Dump(AssistantDumper assistant, Class4 value)
        {
            assistant.IncrementDepth();
            if (assistant.MaximumDepthExceeded())
                return;

            assistant.AddStartObject();
            assistant.AddType("Dogen.TestModels.CSharpModel.Package1.Class4", true/*withSeparator*/);
            assistant.Add("Prop0", value.Prop0);
            assistant.AddEndObject();

            assistant.DecrementDepth();
        }

        public static string Dump(Class4 value)
        {
            var assistant = new AssistantDumper();
            Dump(assistant, value);
            return assistant.Dump();
        }
    }
}
