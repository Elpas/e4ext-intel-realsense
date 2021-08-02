// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2020-2021 Intel Corporation. All Rights Reserved.

using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using System.Web.Script.Serialization;

namespace rsid_wrapper_csharp
{
    internal class DbObj
    {
        public List<rsid.UserFaceprints> db { get; set; }
        public int version { get; set; }
    }

    internal class DatabaseSerializer
    {
        public static byte[] Combine(byte[] first, byte[] second)
        {
            byte[] ret = new byte[first.Length + second.Length];
            Buffer.BlockCopy(first, 0, ret, 0, first.Length);
            Buffer.BlockCopy(second, 0, ret, first.Length, second.Length);
            return ret;
        }

        public static bool MySave(List<(rsid.Faceprints, string)> users, int db_version, string filename)
        {

            try
            {
                byte[] total = new byte[0];
                int nNumUsers = users.Count;
                byte[] aNum = StructureToByteArray(nNumUsers);
                total = Combine(total, aNum);

                foreach (var (faceprintsDb, userIdDb) in users)
                {
                    string name = userIdDb;
                    name = name.PadRight(100, ' ');
                    byte[] bytes = Encoding.ASCII.GetBytes(name);

                    total = Combine(total, bytes);


                    byte[] bt = StructureToByteArray(faceprintsDb);
                    total = Combine(total, bt);

                }

                System.IO.File.WriteAllBytes("c:\\1\\mysave.db", total);
                byte[] b1 = System.IO.File.ReadAllBytes("c:\\1\\mysave.db");
                object f = new rsid.Faceprints();



            }
            catch (Exception e)
            {
                Console.WriteLine("Failed serializing database: " + e.Message);
                return false;
            }
            return true;
        }
        public static void ByteArrayToStructure(byte[] bytearray, ref object obj)
        {
            int len = Marshal.SizeOf(obj);

            IntPtr i = Marshal.AllocHGlobal(len);

            Marshal.Copy(bytearray, 0, i, len);

            obj = Marshal.PtrToStructure(i, obj.GetType());

            Marshal.FreeHGlobal(i);
        }

        public static byte[] StructureToByteArray(object obj)
        {
            int len = Marshal.SizeOf(obj);

            byte[] arr = new byte[len];

            IntPtr ptr = Marshal.AllocHGlobal(len);

            Marshal.StructureToPtr(obj, ptr, true);

            Marshal.Copy(ptr, arr, 0, len);

            Marshal.FreeHGlobal(ptr);

            return arr;
        }
        public static bool Serialize(List<(rsid.Faceprints, string)> users, int db_version, string filename)
        {
            try
            {
                MySave(users, db_version, filename);
                JavaScriptSerializer js = new JavaScriptSerializer();
                DbObj json_root = new DbObj();
                List<rsid.UserFaceprints> jsonstring = new List<rsid.UserFaceprints>();

                foreach (var (faceprintsDb, userIdDb) in users)
                {



                    jsonstring.Add(new rsid.UserFaceprints()
                    {
                        userID = userIdDb,
                        faceprints = faceprintsDb
                    });
                }
                json_root.db = jsonstring;
                json_root.version = db_version;
                using (StreamWriter writer = new StreamWriter(filename))
                {
                    writer.WriteLine(js.Serialize(json_root));//.Replace("\\\"", ""));
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("Failed serializing database: " + e.Message);
                return false;
            }
            return true;
        }


        public static List<(rsid.Faceprints, string)> Deserialize(string filename, out int db_version)
        {
            try
            {
                using (StreamReader reader = new StreamReader(filename))
                {
                    JavaScriptSerializer js = new JavaScriptSerializer();
                    DbObj obj = js.Deserialize<DbObj>(reader.ReadToEnd());
                    var usr_array = new List<(rsid.Faceprints, string)>();
                    foreach (var uf in obj.db)
                    {
                        usr_array.Add((uf.faceprints, uf.userID));
                    }
                    db_version = obj.version;
                    return usr_array;
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("Failed deserializing database: " + e.Message);
                db_version = -1;
                return null;
            }
        }
    }
}